#include "eventdispatcher.hxx"
#include "mutationevent.hxx"
#include "../dom/node.hxx"

namespace DOM { namespace events {

    TypeListenerMap CEventDispatcher::captureListeners;
    TypeListenerMap CEventDispatcher::targetListeners;

    void CEventDispatcher::addListener(xmlNodePtr pNode, OUString aType, const Reference<XEventListener>& aListener, sal_Bool bCapture)
    {
        TypeListenerMap* pTMap = &targetListeners;
        if (bCapture) pTMap = &captureListeners;        

        // get the multimap for the specified type
        ListenerMap *pMap = 0;
        TypeListenerMap::const_iterator tIter = pTMap->find(aType);
        if (tIter == pTMap->end()) {
            // the map has to be created
            pMap = new ListenerMap();
            pTMap->insert(TypeListenerMap::value_type(aType, pMap));
        } else {
            pMap = tIter->second;
        }
        if (pMap !=0)
            pMap->insert(ListenerMap::value_type(pNode, aListener));
    }

    void CEventDispatcher::removeListener(xmlNodePtr pNode, OUString aType, const Reference<XEventListener>& aListener, sal_Bool bCapture)
    {
        TypeListenerMap *pTMap = &targetListeners;
        if (bCapture) pTMap = &captureListeners;
        
        // get the multimap for the specified type
        TypeListenerMap::const_iterator tIter = pTMap->find(aType);
        if (tIter != pTMap->end()) {
            ListenerMap *pMap = tIter->second;
            // find listeners of specied type for specified node
            ListenerMap::iterator iter = pMap->find(pNode);
            ListenerMap::const_iterator ibound = pMap->upper_bound(pNode);
            while (iter != ibound)
            {
                // erase all references to specified listener
                if((iter->second).is() && (iter->second) == aListener)
                {
                    ListenerMap::iterator i2 = iter;
                    iter++;
                    pMap->erase(i2);
                }
                else
                    iter++;
            }
        }
    }
    
    void CEventDispatcher::callListeners(xmlNodePtr pNode, OUString aType, const Reference< XEvent >& xEvent, sal_Bool bCapture)
    {        
        TypeListenerMap *pTMap = &targetListeners;
        if (bCapture) pTMap = &captureListeners;
        
        // get the multimap for the specified type
        TypeListenerMap::const_iterator tIter = pTMap->find(aType);
        if (tIter != pTMap->end()) {
            ListenerMap *pMap = tIter->second;
            ListenerMap::const_iterator iter = pMap->find(pNode);
            if( iter == pMap->end() ) return;
            ListenerMap::const_iterator ibound = pMap->upper_bound(pNode);
            ListenerPairVector lv(iter, ibound);
            ListenerPairVector::const_iterator liter = lv.begin();
            while (liter != lv.end())
            {
                if((liter->second).is())
                {                    
                    (liter->second)->handleEvent(xEvent);
                }
                liter++;
            }
        }
    }

    sal_Bool CEventDispatcher::dispatchEvent(xmlNodePtr aNodePtr, const Reference< XEvent >& aEvent)
    {
        CEvent *pEvent = 0; // pointer to internal event representation
        Reference< XEvent > xEvent; // reference to the event being dispatched;

        OUString aType = aEvent->getType();
        if (aType.compareToAscii("DOMSubtreeModified")          == 0||
            aType.compareToAscii("DOMNodeInserted")             == 0||
            aType.compareToAscii("DOMNodeRemoved")              == 0||
            aType.compareToAscii("DOMNodeRemovedFromDocument")  == 0||
            aType.compareToAscii("DOMNodeInsertedIntoDocument") == 0||
            aType.compareToAscii("DOMAttrModified")             == 0||
            aType.compareToAscii("DOMCharacterDataModified")    == 0)
        {                
                Reference< XMutationEvent > aMEvent(aEvent, UNO_QUERY);
                // dispatch a mutation event
                // we need to clone the event in order to have complete control 
                // over the implementation
                CMutationEvent* pMEvent = new CMutationEvent;
                pMEvent->initMutationEvent(
                    aType, aMEvent->getBubbles(), aMEvent->getCancelable(),
                    aMEvent->getRelatedNode(), aMEvent->getPrevValue(),
                    aMEvent->getNewValue(), aMEvent->getAttrName(), 
                    aMEvent->getAttrChange());    
                pEvent = pMEvent;                
        }
        else // generic event
        {
            pEvent = new CEvent;
            pEvent->initEvent(
                aType, aEvent->getBubbles(), aEvent->getCancelable());
            

        }
        pEvent->m_target = Reference< XEventTarget >(DOM::CNode::get(aNodePtr));
        pEvent->m_currentTarget = aEvent->getCurrentTarget();
        pEvent->m_time = aEvent->getTimeStamp();
        xEvent = Reference< XEvent >(static_cast< CEvent* >(pEvent));


        // build the path from target node to the root
        NodeVector captureVector;  
        Reference< XUnoTunnel > aTunnel(xEvent->getTarget(), UNO_QUERY_THROW);
        xmlNodePtr cur = (xmlNodePtr)aTunnel->getSomething(Sequence< sal_Int8 >());
        while (cur != NULL)
        {
            captureVector.push_back(cur);
            cur = cur->parent;
        }

        // the caputre vector now holds the node path from target to root
        // first we must search for capture listernes in order root to 
        // to target. after that, any target listeners have to be called
        // then bubbeling phase listeners are called in target to root
        // order
        NodeVector::const_iterator inode;                
        
        // start at the root
        inode = captureVector.end();
        inode--;
        if (inode != captureVector.end())
        {
            // capturing phase:
            pEvent->m_phase = PhaseType_CAPTURING_PHASE;
            while (inode != captureVector.begin())
            {  
                //pEvent->m_currentTarget = *inode;
                pEvent->m_currentTarget = Reference< XEventTarget >(CNode::get(*inode));
                callListeners(*inode, aType, xEvent, sal_True);
                if  (pEvent->m_canceled) return sal_True;
                inode--;
            }

            // target phase
            pEvent->m_phase = PhaseType_AT_TARGET;
            callListeners(*inode, aType, xEvent, sal_False);
            if  (pEvent->m_canceled) return sal_True;
            // bubbeling phase
            inode++;
            if (aEvent->getBubbles()) {
                pEvent->m_phase = PhaseType_BUBBLING_PHASE;
                while (inode != captureVector.end())
                {
                    pEvent->m_currentTarget = Reference< XEventTarget >(CNode::get(*inode));
                    callListeners(*inode, aType, xEvent, sal_False);
                    if  (pEvent->m_canceled) return sal_True;
                    inode++;
                }
            }
        }                
        return sal_True;
    }
}}