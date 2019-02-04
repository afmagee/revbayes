//
//  StochasticBranchStateTimesMonitor.h
//  RevBayes_development_branch
//
//  Created by will freyman on 4/25/18.
//  Copyright (c) 2018 will freyman. All rights reserved.
//


#include "StochasticBranchStateTimesMonitor.h"
#include "DagNode.h"
#include "Model.h"
#include "Monitor.h"
#include "RbFileManager.h"
#include "StochasticNode.h"
#include "StateDependentSpeciationExtinctionProcess.h"

using namespace RevBayesCore;


/* Constructor for state dependent birth death process */
StochasticBranchStateTimesMonitor::StochasticBranchStateTimesMonitor(StochasticNode<Tree>* ch, unsigned long g, const std::string &fname, const std::string &del) : AbstractFileMonitor(ch, g, fname, del, false, false, false),
    cdbdp( ch )
{
    // the cdbdp is both the tree and character evolution model
    addVariable( cdbdp );
    tree = static_cast< StochasticNode<Tree> *>( cdbdp );
}



/**
 * Copy constructor.
 */
StochasticBranchStateTimesMonitor::StochasticBranchStateTimesMonitor( const StochasticBranchStateTimesMonitor &m) : AbstractFileMonitor( m ),
    tree( m.tree ),
    cdbdp( m.cdbdp )
{
    
}


/**
 * Destructor.
 */
StochasticBranchStateTimesMonitor::~StochasticBranchStateTimesMonitor()
{
    
}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'B'.
 *
 * \return A new copy of myself
 */
StochasticBranchStateTimesMonitor* StochasticBranchStateTimesMonitor::clone(void) const
{
    
    return new StochasticBranchStateTimesMonitor(*this);
}


/**
 * Monitor value at given generation.
 *
 * \param[in]   gen    The current generation.
 */
void StochasticBranchStateTimesMonitor::monitorVariables(unsigned long gen)
{

    StateDependentSpeciationExtinctionProcess *sse = dynamic_cast<StateDependentSpeciationExtinctionProcess*>( &cdbdp->getDistribution() );
    size_t num_nodes = tree->getValue().getNumberOfNodes();
    std::vector<std::string*> character_histories( num_nodes );
    
    // draw stochastic character map
    sse->drawStochasticCharacterMap( character_histories );
    std::vector<double> time_in_states = sse->getTimeInStates(); 

    // print to monitor file
    for (int i = 0; i < time_in_states.size(); i++)
    {
        // add a separator before every new element
        out_stream << separator;
            
        out_stream << time_in_states[i];
        
    }
    
}


/**
 * Print header for monitored values
 */
void StochasticBranchStateTimesMonitor::printFileHeader()
{

    StateDependentSpeciationExtinctionProcess *sse = dynamic_cast<StateDependentSpeciationExtinctionProcess*>( &cdbdp->getDistribution() );
    std::vector<double> time_in_states = sse->getTimeInStates(); 
    
    for (int i = 0; i < time_in_states.size(); i++)
    {
        out_stream << separator;
        out_stream << i + 1;
    }
    
}


void StochasticBranchStateTimesMonitor::swapNode(DagNode *oldN, DagNode* newN)
{
    
    if ( oldN == tree )
    {
        tree = static_cast< TypedDagNode<Tree> *>( newN );
    }
    else if ( oldN == cdbdp )
    {
        cdbdp = static_cast< StochasticNode<Tree> *>( newN );
        tree = static_cast< StochasticNode<Tree> *>( newN );
    }
    
    AbstractFileMonitor::swapNode( oldN, newN );
    
}


