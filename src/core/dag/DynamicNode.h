/**
 * @file
 * This file contains the declaration of the dynamic DAG node class, which is our base class for all dynamic DAG nodes (opposed to constant DAG nodes).
 * Dynamic DAG nodes can change their value during an anaylis, and hence they are dynamic. Deterministic and stochastic DAG nodes derive from this class.
 * A dynamic DAG node has parents which are the parameters of the function or distribution.
 *
 * @brief Declaration of the typed base class DagNode.
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2012-06-17, version 1.0
 * @interface TypedDagNode
 *
 * $Id$
 */

#ifndef DynamicNode_H
#define DynamicNode_H

#include "TypedDagNode.h"
#include <set>

namespace RevBayesCore {
    
    template<class valueType>
    class DynamicNode : public TypedDagNode<valueType> {
    
    public:
    
        DynamicNode(const std::string &n);
        DynamicNode(const DynamicNode &n);
        virtual                                            ~DynamicNode(void);                                                              //!< Virtual destructor

        // pure virtual methods
        virtual DynamicNode<valueType>*                     clone(void) const = 0;
        virtual double                                      getLnProbability(void) = 0;
        virtual double                                      getLnProbabilityRatio(void) = 0;

        // public methods
        DagNode*                                            cloneDAG(std::map<const DagNode*, DagNode*> &nodesMap) const;                   //!< Clone the entire DAG which is connected to this node

        // this function provided for derived classes used in the language layer, which need to override it
        virtual const std::string&                          getRevTypeOfValue(void);                                                        //!< Get Rev language type of value

    protected:
        virtual void                                        keepMe(DagNode* affecter);                                                      //!< Keep value of this and affected nodes
        virtual void                                        restoreMe(DagNode *restorer);                                                   //!< Restore value of this node
        virtual void                                        touchMe(DagNode *toucher);                                                      //!< Tell affected nodes value is reset

    
        // members
        bool                                                touched;                                                                        //!< Is touched by move?
    };

}

#include "RbException.h"

template<class valueType>
RevBayesCore::DynamicNode<valueType>::DynamicNode( const std::string &n ) : TypedDagNode<valueType>( n ), touched( true ) {
    // nothing to do here
}


template<class valueType>
RevBayesCore::DynamicNode<valueType>::DynamicNode( const DynamicNode<valueType> &n ) : TypedDagNode<valueType>( n ), touched( true ) {
    // nothing to do here
}


template<class valueType>
RevBayesCore::DynamicNode<valueType>::~DynamicNode( void ) {
    // We don't own the parents and hence we don't delete them. The owner of the graph needs to do that. Just tell them we are gone forever ... :(
}


/** Clone the entire graph: clone children, swap parents */
template<class valueType>
RevBayesCore::DagNode* RevBayesCore::DynamicNode<valueType>::cloneDAG( std::map<const DagNode*, DagNode* >& newNodes ) const {
    
    // Return our clone if we have already been cloned
    if ( newNodes.find( this ) != newNodes.end() )
        return ( newNodes[ this ] );
    
    // Get pristine copy
    DynamicNode* copy = clone();
    
    // Add this node to the map
    newNodes[ this ] = copy;
    
    // Note that functions and distributions have copies of DAG node pointers, so the copy and
    // the original will have the same parents after the call to clone(). In fact, this is the
    // desired behavior to not interfere with the cloning of the entire DAG in this function.
    // Thus, all dynamic DAG nodes should adopt this convention.
    std::set<const DagNode*> parents = this->getParents();

    for ( std::set<const DagNode*>::const_iterator i = parents.begin(); i != parents.end(); ++i )
    {
        const DagNode *theParam = (*i);
        
        // remove myself from the param as a child, because cloning the param will call of cloning this already cloned node
        theParam->removeChild( copy );
    }
    
    for ( std::set<const DagNode*>::const_iterator i = parents.begin(); i != parents.end(); ++i )
    {
        // get the i-th member and get the clone back
        const DagNode *theParam = (*i);
        
        // if we already have cloned this parent (parameter), then we will get the previously created clone
        DagNode* theParamClone = theParam->cloneDAG( newNodes );
        
        // add myself back as a child so that the swapping works
        theParam->addChild( copy );
        
        // set the clone of the member as the member of the clone
        copy->swapParent( theParam, theParamClone);
    }
    
    /* Make sure the children clone themselves */
    for( std::set<DagNode*>::const_iterator i = this->children.begin(); i != this->children.end(); i++ ) 
    {
        (*i)->cloneDAG( newNodes );
    }
    
    return copy;
}


/**
 * This function returns the Rev language type of the value. When used in the Rev
 * language layer, a DAG node must know the Rev language type of its value, or
 * construction of dynamic variables will not be safe. Here we just throw an
 * error, as a core DAG node need not know and should not know the language type
 * of its value.
 */
template<class valueType>
const std::string& RevBayesCore::DynamicNode<valueType>::getRevTypeOfValue(void)
{
    throw RbException( "Rev language type of dynamic DAG node value not known" );
}


/**
 * Keep the current value of the node.
 * At this point, we also need to make sure we update the stored ln probability.
 */
template<class valueType>
void RevBayesCore::DynamicNode<valueType>::keepMe( DagNode* affecter ) {
    
    if ( touched ) 
    {
        touched = false;
    }
    
    
}


/** Restore the old value of the node and tell affected */
template<class valueType>
void RevBayesCore::DynamicNode<valueType>::restoreMe(DagNode *restorer) {
    
    if ( touched ) 
    {
        touched = false;
    }
    
}

/** touch this node for recalculation */
template<class valueType>
void RevBayesCore::DynamicNode<valueType>::touchMe( DagNode *toucher ) {
    
    if (!touched) 
    {
        // Store the current lnProb 
        touched      = true;
    }
        
}



#endif

