
#include <memory>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <map>
#include <list>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include "expressionparser.hh"
#include "sipattrextractor.hh"

#include <regex.h>

#include "log/logmanager.hh"


using namespace::std;


static string tf(bool value) {
	return value?"true":"false";
}

BooleanExpression::~BooleanExpression(){}

long BooleanExpression::ptr() {
	return (long)this;
}

#ifndef NO_SOFIA
bool BooleanExpression::eval ( const sip_t* sip ) {
	SipAttributes attr(sip);
	auto generator = getGenerator();
	return generator(&attr);
}
#endif

bool BooleanExpression::eval(const SipAttributes *args){
	return getGenerator()(args);
}


class EmptyBooleanExpression : public BooleanExpression {
public:
	EmptyBooleanExpression() {}
	GeneratorFun_t getGenerator() {
		return [](const SipAttributes*args) { return true; };
	}
};

shared_ptr<BooleanExpression> parseExpression(const string & expr, size_t *newpos);

/*
 * May return empty expression
 */
std::shared_ptr<BooleanExpression> BooleanExpression::parse(const std::string &str) {
	if (str.empty()) return make_shared<EmptyBooleanExpression>();
	size_t pos=0;
	auto expr = parseExpression(str, &pos);
	return expr;
}

static bool logEval=false;
void log_boolean_expression_evaluation(bool value) { logEval=value; }

static bool logParse=false;
void log_boolean_expression_parsing(bool value) { logParse=value; }

#define LOGPARSE if (logParse) SLOGI
#define LOGEVAL if (logEval) SLOGI




class VariableOrConstant {
	list<string> mValueList;
public:
	virtual ~VariableOrConstant() {}
	virtual const std::string &get(const SipAttributes *args)=0;
	bool defined(const SipAttributes *args) {
		try {
			get(args);
			return true;
		} catch (exception &) {}
		return false;
	}
	const list<string> &getAsList(const SipAttributes *args) {
		string s=get(args);
		mValueList.clear();

		size_t pos1=0;
		size_t pos2=0;
		for (pos2=0; pos2 < s.size(); ++pos2) {
			if (s[pos2] != ' ') {
				if (s[pos1] == ' ') pos1=pos2;
				continue;
			}
			if (s[pos2] == ' ' && s[pos1] == ' ') {
				pos1=pos2;
				continue;
			}
			mValueList.push_back(s.substr(pos1, pos2-pos1));
			pos1=pos2;
		}

		if (pos1 != pos2)
			mValueList.push_back(s.substr(pos1, pos2-pos1));

		return mValueList;
	}
};

class Constant : public VariableOrConstant {
	string mVal;
public:
	Constant(const std::string &val): mVal(val) {
		LOGPARSE << "Creating constant XX" << val << "XX";
	}
	virtual const std::string &get(const SipAttributes *args) {
		return mVal;
	}
};

class Variable : public VariableOrConstant {
	string mId;
	string mVal;
public:
	Variable(const std::string &val): mId(val) {
		LOGPARSE << "Creating variable XX" << val << "XX";
	}
	virtual const std::string &get(const SipAttributes *args) {
		try {
			mVal=args->get(mId);
		} catch (exception &e) {
			LOGEVAL << "GET " << mId << " : " << e.what();
			throw;
		}
		return mVal;
	}
};

class TrueFalseExpression : public BooleanExpression {
	string mId;
	bool is_final;
	bool final_value;
public:
	TrueFalseExpression(const string &value) : mId(value){
		if( mId == "true" || mId == "false"){
			is_final = true;
			final_value = (mId == "true") ? true : false;
		}
	}
	GeneratorFun_t getGenerator(){
		auto id = mId;
		return [this, id](const SipAttributes* args){
			// TODO: make SipArgs return a generator too
			if (is_final) return final_value;
			return args->isTrue(id);
		};
	}
};

class LogicalAnd : public BooleanExpression{
	GeneratorFun_t gen1,gen2;
public:
	LogicalAnd(shared_ptr<BooleanExpression> exp1, shared_ptr<BooleanExpression> exp2): gen1(exp1->getGenerator()), gen2(exp2->getGenerator()){
		LOGPARSE << "Creating LogicalAnd";
	}
	GeneratorFun_t getGenerator() {
		auto g1 = gen1, g2=gen2;
		return [this, g1, g2](const SipAttributes*args){
			bool g1res = g1(args);
			bool g2res =  g2(args);
			return g1res && g2res;
		};
	}
};


class LogicalOr : public BooleanExpression{
	GeneratorFun_t gen1;
	GeneratorFun_t gen2;
public:
	LogicalOr(shared_ptr<BooleanExpression> exp1, shared_ptr<BooleanExpression> exp2) {
		gen1 = exp1->getGenerator();
		gen2 = exp2->getGenerator();
	}
	GeneratorFun_t getGenerator() {
		auto g1 = gen1, g2 = gen2;
		return [this, g1, g2](const SipAttributes*args){
			bool g1res = g1(args);
			bool g2res = g2(args);
			return g1res || g2res;
		};
	}
};

class LogicalNot : public BooleanExpression{
public:
	LogicalNot(shared_ptr<BooleanExpression> exp) :gen1(exp->getGenerator()){
		LOGPARSE << "Creating LogicalNot";
	}
	GeneratorFun_t getGenerator() {
		auto g = gen1;
		return [this, g](const SipAttributes*args){
			return ! g(args);
		};
	}
private:
	GeneratorFun_t gen1;
};


class EqualsOp : public BooleanExpression{
public:
	EqualsOp(shared_ptr<VariableOrConstant> var1, shared_ptr<VariableOrConstant> var2) : mVar1(var1), mVar2(var2){
		LOGPARSE << "Creating EqualsOperator";
	}
	GeneratorFun_t getGenerator() {
		auto v1 = mVar1, v2 = mVar2;
		return [this, v1, v2](const SipAttributes*args){
			bool res=v1->get(args)==v2->get(args);
			LOGEVAL << "evaluating "<< v1->get(args)<< " == "<< v2->get(args)<< " : " << (res?"true":"false");
			return res;
		};
	}
private:
	shared_ptr<VariableOrConstant> mVar1,mVar2;
};


class UnEqualsOp : public BooleanExpression {
public:
	UnEqualsOp(shared_ptr<VariableOrConstant> var1, shared_ptr<VariableOrConstant> var2)
	: mVar1(var1), mVar2(var2){
		LOGPARSE << "Creating UnEqualsOperator";
	}
	GeneratorFun_t getGenerator() {
		return [this](const SipAttributes*args){
			bool res=mVar1->get(args)!=mVar2->get(args);
			LOGEVAL << "evaluating " << mVar1->get(args) << " != " << mVar2->get(args) << " : " << (res?"true":"false");
			return res;
		};
	}
private:
	shared_ptr<VariableOrConstant> mVar1,mVar2;
};


class NumericOp : public BooleanExpression{
	shared_ptr<VariableOrConstant> mVar;
public:
	NumericOp(shared_ptr<VariableOrConstant> var) : mVar(var){
		LOGPARSE << "Creating NumericOperator";
	}
	GeneratorFun_t getGenerator() {
		return [this](const SipAttributes*args){
			string var=mVar->get(args);
			bool res=true;
			for (auto it=var.begin(); it != var.end(); ++it) {
				if (!isdigit(*it)) {
					res=false;
					break;
				}
			}
			LOGEVAL << "evaluating " << var << " is numeric : " << (res?"true":"false");
			return res;
		};
	}
};


class DefinedOp : public BooleanExpression{
	shared_ptr<VariableOrConstant> mVar;
	string mName;
public:
	DefinedOp(string name, shared_ptr<VariableOrConstant> var) : mVar(var), mName(name){
		LOGPARSE << "Creating DefinedOperator";
	}
	GeneratorFun_t getGenerator() {
		auto v = mVar;
		return [this, v](const SipAttributes*args){
			bool res=v->defined(args);
			LOGEVAL << "evaluating is defined for " << mName << (res?"true":"false");
			return res;
		};
	}
};

class Regex : public BooleanExpression{
	shared_ptr<VariableOrConstant> mInput;
	shared_ptr<Constant> mPattern;
	regex_t preg;
	char error_msg_buff[100];
public:
	Regex(shared_ptr<VariableOrConstant> input, shared_ptr<Constant> pattern) : mInput(input),mPattern(pattern){
		LOGPARSE << "Creating Regular Expression";
		string p= pattern->get(NULL);
		int err = regcomp(&preg,p.c_str(), REG_NOSUB | REG_EXTENDED);
		if (err !=0) throw invalid_argument("couldn't compile regex " + p);
	}
	~Regex() {
		regfree(&preg);
	}
	GeneratorFun_t getGenerator() {
		return [this](const SipAttributes*args){
			string input=mInput->get(args);
			int match = regexec(&preg, input.c_str(), 0, NULL, 0);
			bool res;
			switch (match) {
			case 0:
				res=true;
				break;
			case REG_NOMATCH:
				res=false;
				break;
			default:
				regerror (match, &preg, error_msg_buff, sizeof(error_msg_buff));
				throw invalid_argument("Error evaluating regex " + string(error_msg_buff));
			}

			LOGEVAL << "evaluating " << input << " is regex  " << mPattern->get(NULL) << " : " << (res?"true":"false");
			return res;
		};
	}
};

class ContainsOp : public BooleanExpression{
	shared_ptr<VariableOrConstant> mVar1,mVar2;
public:
	ContainsOp(shared_ptr<VariableOrConstant> var1, shared_ptr<VariableOrConstant> var2) : mVar1(var1), mVar2(var2){}
	GeneratorFun_t getGenerator() {
		auto v1 = mVar1, v2 = mVar2;
		return [this, v1, v2](const SipAttributes*args){
			bool res=v1->get(args).find(v2->get(args))!=std::string::npos;
			LOGEVAL << "evaluating " << v1->get(args) << " contains " << v2->get(args) << " : " << (res?"true":"false");
			return res;
		};
	}
};


class InOp : public BooleanExpression{
public:
	InOp(shared_ptr<VariableOrConstant> var1, shared_ptr<VariableOrConstant> var2) : mVar1(var1), mVar2(var2){}
	GeneratorFun_t getGenerator() {
		auto v1 = mVar1, v2 = mVar2;
		return [this, v1, v2](const SipAttributes*args){
			bool res=false;
			const list<string> &values=v2->getAsList(args);
			const string &varValue=v1->get(args);

			LOGEVAL << "Evaluating '" << varValue << "' IN {" << v2->get(args) << "}";
			for (auto it=values.begin(); it != values.end(); ++it) {
				LOGEVAL << "Trying '" <<  *it << "'";
				if (varValue == *it) {
					res=true;
					break;
				}
			}
			LOGEVAL << "->" << (res?"true":"false");
			return res;
		};
	}
private:
	shared_ptr<VariableOrConstant> mVar1,mVar2;
};

static size_t find_first_non_word(const string &expr, size_t offset) {
	size_t i;
	for(i=offset;i<expr.size();++i){
		char c=expr[i];
		if (c != '-' && c != '.' && !isalnum(c)) return i;
	}
	return i;
}


static shared_ptr<Variable> buildVariable(const string & expr, size_t *newpos){
	LOGPARSE << "buildVariable working on XX" << expr << "XX";
	while (expr[*newpos]==' ') *newpos+=1;

	size_t eow=find_first_non_word(expr, *newpos);
	if (eow <= *newpos && expr.size() > eow) {
		throw invalid_argument("no variable recognized in X" + expr.substr(*newpos,string::npos)+"XX");
	}
	size_t len=eow-*newpos;
	auto var=expr.substr(*newpos, len);
	*newpos+=len;
	return make_shared<Variable>(var);
}

static shared_ptr<Constant> buildConstant(const string & expr, size_t *newpos){
	LOGPARSE << "buildConstant working on XX" << expr << "XX";
	while (expr[*newpos]==' ') *newpos+=1;

	if (expr[*newpos]!='\'')
		throw invalid_argument("Missing quote at start of " + expr);

	size_t end=expr.find_first_of('\'',*newpos+1);
	if (end!=string::npos){
		size_t len=end-*newpos-1;
		string cons=expr.substr(*newpos+1,len);
		*newpos+=len +2; // remove the two '
		return make_shared<Constant>(cons);
	}else {
		throw invalid_argument("Missing quote around " + expr);
	}
}

static shared_ptr<VariableOrConstant> buildVariableOrConstant(const string & expr, size_t *newpos){
	LOGPARSE << "buildVariableOrConstant working on XX" << expr << "XX";
	while (expr[*newpos]==' ') *newpos+=1;

	if (expr[*newpos]=='\''){
		auto constant=buildConstant(expr, newpos);
		return dynamic_pointer_cast<VariableOrConstant>(constant);
	}else{
		auto variable=buildVariable(expr, newpos);
		return dynamic_pointer_cast<VariableOrConstant>(variable);
	}
}

static size_t find_matching_closing_parenthesis(const string &expr, size_t offset){
	size_t i;
	int match=1;
	for(i=offset;i<expr.size();++i){
		if (expr[i]=='(') ++match;
		else if (expr[i]==')') --match;
		if (match==0) return i;
	}
	return string::npos;
}

static bool isKeyword(const string &expr, size_t *newpos, const string &keyword) {
	size_t pos=*newpos;
	size_t keyLen=keyword.size();
	size_t availableLen=expr.size()-pos;
	if (availableLen < keyLen) return false;

	for (size_t i = 0; i < keyLen; ++i) {
		if (expr[pos+i] != keyword[i]) return false;
	}

	if (availableLen > keyLen && isalnum(expr[pos+keyLen])) return false;

	*newpos+=keyLen;
	LOGPARSE << "Recognized keyword '" << keyword << "'";
	return true;
}

static void printState(const string &str, size_t pos) {
	LOGPARSE << "Working on " << str;
	ostringstream oss;
	for (size_t i=0; i < pos + 11; ++i) oss << " ";
	oss << "^";
	if (pos < str.size()) {
		oss << str.substr(pos, 1);
	}
	LOGPARSE << oss.str().c_str();
}

shared_ptr<BooleanExpression> parseExpression(const string & expr, size_t *newpos){
	size_t i;

	LOGPARSE << "Parsing expression " << expr;
	shared_ptr<BooleanExpression> cur_exp;
	shared_ptr<VariableOrConstant> cur_var;

	for (i=0;i<expr.size();){
		size_t j=0;
		printState(expr, *newpos+i);
		switch(expr[i]){
		case '(':
		{
			size_t end=find_matching_closing_parenthesis(expr,i+1);
			if (end!=string::npos){
				cur_exp=parseExpression(expr.substr(i+1,end-i-1),&j);
				i=end+1;
			}else {
				throw invalid_argument("Missing parenthesis around " + expr);
			}
		}
		break;
		case '&':
			if (expr[i+1]=='&'){
				if (!cur_exp){
					throw new logic_error("&& operator expects first operand.");
				}
				i+=2;
				cur_exp=make_shared<LogicalAnd>(cur_exp,parseExpression(expr.substr(i),&j));
				i+=j;
			}else{
				throw new logic_error("Bad operator '&'");
			}
			break;
		case '|':
			if (expr[i+1]=='|'){
				if (!cur_exp){
					throw new logic_error("|| operator expects first operand.");
				}
				i+=2;
				cur_exp=make_shared<LogicalOr>(cur_exp,parseExpression(expr.substr(i),&j));
				i+=j;
			}else{
				throw invalid_argument("Bad operator '|'");
			}
			break;
		case '!':
			if (expr[i+1]=='='){
				if (!cur_var){
					throw invalid_argument("!= operator expects first variable or const operand.");
				}
				i+=2;
				cur_exp=make_shared<UnEqualsOp>(cur_var,buildVariableOrConstant(expr.substr(i),&j));
			}
			else {
				if (cur_exp){
					throw invalid_argument("Parsing error around '!'");
				}
				i++;
				for (;expr[i]==' ';++i); //skip spaces (we are fair)

				if (isKeyword(expr.substr(i), &(j=0), "true")) {
					i+=j; j=0;
					cur_exp=make_shared<TrueFalseExpression>("true");
				} else if (isKeyword(expr.substr(i), &(j=0), "false")) {
					i+=j; j=0;
					cur_exp=make_shared<TrueFalseExpression>("false");
				} else if (isKeyword(expr.substr(i), &(j=0), "numeric")) {
					i+=j; j=0;
					auto var=buildVariableOrConstant(expr.substr(i),&j);
					cur_exp=make_shared<NumericOp>(var);
				} else if (isKeyword(expr.substr(i), &j, "defined")) {
					i+=j; j=0;
					auto var=buildVariableOrConstant(expr.substr(i),&j);
					cur_exp=make_shared<DefinedOp>(expr.substr(i, j), var);
				} else if (expr[i]=='(') {
					size_t end=find_matching_closing_parenthesis(expr,i+1);
					if (end!=string::npos){
						cur_exp=parseExpression(expr.substr((i+1),end-(i+1)),&j);
						i=end+1;
						j=0; // no use
					}else {
						throw invalid_argument("Missing parenthesis around " + expr);
					}
				} else {
					ostringstream oss; oss << expr[i];
					LOGPARSE << ">" << oss.str();
					throw invalid_argument("! operator expects boolean value or () expression.");

				}

				// Take the negation!
				cur_exp=make_shared<LogicalNot>(cur_exp);

			}
			i+=j;
			break;
		case '=':
			if (expr[i+1]=='='){
				if (!cur_var){
					throw invalid_argument("== operator expects first variable or const operand.");
				}
				i+=2;
				cur_exp=make_shared<EqualsOp>(cur_var,buildVariableOrConstant(expr.substr(i),&j));
				i+=j;
			}else{
				throw invalid_argument("Bad operator =");
			}
			break;
		case ' ':
			LOGPARSE << "skipping space";
			i++;
			break;
		case 'c':
			if (isKeyword(expr.substr(i), &j, "contains")) {
				i+=j;
				j=0;
				auto rightVar= buildVariableOrConstant(expr.substr(i),&j);
				cur_exp=make_shared<ContainsOp>(cur_var, rightVar);
				i+=j;
			} else {
				cur_var=buildVariableOrConstant(expr.substr(i),&j);
				i+=j;j=0;
			}
			break;
		case 'd':
			if (isKeyword(expr.substr(i), &j, "defined")) {
				i+=j;
				j=0;
				auto rightVar= buildVariableOrConstant(expr.substr(i),&j);
				cur_exp=make_shared<DefinedOp>(expr.substr(i, j), rightVar);
				i+=j;
			} else {
				cur_var=buildVariableOrConstant(expr.substr(i),&j);
				i+=j;j=0;
			}
			break;
		case 'r':
			if (isKeyword(expr.substr(i), &j, "regex")) {
				i+=j;
				j=0;
				auto pattern= buildConstant(expr.substr(i),&j);
				cur_exp=make_shared<Regex>(cur_var, pattern);
				i+=j;
			} else {
				cur_var=buildVariableOrConstant(expr.substr(i),&j);
				i+=j;j=0;
			}
			break;
		case 'i':
			if (isKeyword(expr.substr(i), &j, "in")) {
				i+=j; j=0;
				auto rightVar= buildVariableOrConstant(expr.substr(i),&j);
				cur_exp=make_shared<InOp>(cur_var, rightVar);
				i+=j;
			} else if (isKeyword(expr.substr(i), &j, "is_request")) {
				i+=j; j=0;
				cur_exp=make_shared<TrueFalseExpression>("is_request");
			} else if (isKeyword(expr.substr(i), &j, "is_response")) {
				i+=j; j=0;
				cur_exp=make_shared<TrueFalseExpression>("is_response");
			} else {
				cur_var=buildVariableOrConstant(expr.substr(i),&j);
				i+=j;j=0;
			}
			break;
		case 't':
			if (isKeyword(expr.substr(i), &j, "true")) {
				i+=j; j=0;
				cur_exp=make_shared<TrueFalseExpression>("true");
			} else {
				cur_var=buildVariableOrConstant(expr.substr(i),&j);
				i+=j;j=0;
			}
			break;
		case 'f':
			if (isKeyword(expr.substr(i), &j, "false")) {
				i+=j; j=0;
				cur_exp=make_shared<TrueFalseExpression>("false");
			} else {
				cur_var=buildVariableOrConstant(expr.substr(i),&j);
				i+=j;j=0;
			}
			break;
		case 'n':
			if (isKeyword(expr.substr(i), &j, "numeric")) {
				if (cur_exp || cur_var){
					throw invalid_argument("Parsing error around 'numeric'");
				}
				i+=j; j=0;
				auto var=buildVariableOrConstant(expr.substr(i),&j);
				cur_exp=make_shared<NumericOp>(var);
				i+=j; j=0;
				// fixme should check all is finished now
			} else if (isKeyword(expr.substr(i), &j, "nin") || isKeyword(expr.substr(i), &j, "notin")) {
				i+=j; j=0;
				auto rightVar= buildVariableOrConstant(expr.substr(i),&j);
				auto in=make_shared<InOp>(cur_var, rightVar);
				cur_exp=make_shared<LogicalNot>(in);
				i+=j;
			} else {
				cur_var=buildVariableOrConstant(expr.substr(i),&j);
				i+=j;j=0;
			}
			break;
		default:
			cur_var=buildVariableOrConstant(expr.substr(i),&j);
			i+=j;j=0;
			break;
		}
	}
	*newpos+=i;
	return cur_exp;
};



