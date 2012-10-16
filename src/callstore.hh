/*
	Flexisip, a flexible SIP proxy server with media capabilities.
    Copyright (C) 2010  Belledonne Communications SARL.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef callstore_hh
#define callstore_hh

#include "agent.hh"
#include <list>

class CallContextBase{
	public:
		CallContextBase(sip_t *sip);
		bool match(Agent *ag, sip_t *sip, bool stateful = false);
		bool isNewInvite(sip_t *sip);
		void storeNewInvite(msg_t *orig);
		msg_t *getLastForwardedInvite()const;
		virtual void dump();
		virtual bool isInactive(time_t cur){
			return false;
		}
		su_home_t *getHome(){
			return &mHome;
		}
		virtual ~CallContextBase();
		const std::string & getCallerTag()const{
			return mCallerTag;
		}
		const std::string & getCalleeTag()const{
			return mCalleeTag;
		}
		uint32_t getViaCount() const {
			return mViaCount;
		}
	private:
		su_home_t mHome;
		sip_from_t *mFrom;
		msg_t *mInvite;
		uint32_t mCallHash;
		uint32_t mInvCseq;
		uint32_t mResCseq;
		uint32_t mAckCseq;
		std::string mCallerTag;
		std::string mCalleeTag;
		std::string mBranch; /*of the via of the first Invite request*/
		uint32_t mViaCount;
};

class CallStore{
	public:
		CallStore();
		~CallStore();
		void store(const std::shared_ptr<CallContextBase> &ctx);
		std::shared_ptr<CallContextBase> find(Agent *ag, sip_t *sip, bool stateful = false);
		void remove(const std::shared_ptr<CallContextBase> &ctx);
		void removeAndDeleteInactives();
		void setCallStatCounters(StatCounter64 *invCount, StatCounter64 *invFinishedCount) {
			mCountCalls=invCount;
			mCountCallsFinished=invFinishedCount;
		}
		void dump();
		const std::list<std::shared_ptr<CallContextBase>> &getList()const{
			return mCalls;
		}
	private:
		std::list<std::shared_ptr<CallContextBase>> mCalls;
		StatCounter64 *mCountCalls;
		StatCounter64 *mCountCallsFinished;
};


#endif
