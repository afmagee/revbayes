#ifndef RlBranchRateJumpProcess_H
#define RlBranchRateJumpProcess_H

#include "BranchRateJumpProcess.h"
#include "RlTypedDistribution.h"
#include "RealPos.h"
#include "Vector.h"

namespace RevLanguage {
    
    
    /**
     * The RevLanguage wrapper of the BranchRateJumpProcess.
     *
     * The RevLanguage wrapper of the branch-rate jump process.
     * This process is used to get branch-wise rate multipliers, e.g., for the random local clock.
     * See BranchRateJumpProcess.h
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2014-03-29, version 1.0
     *
     */
    class BranchRateJumpProcess :  public TypedDistribution< Vector<RealPos>  > {
        
    public:
        BranchRateJumpProcess( void );
        
        // Basic utility functions
        BranchRateJumpProcess*                      clone(void) const;                                                                              //!< Clone the object
        static const std::string&                   getClassName(void);                                                                             //!< Get class name
        static const TypeSpec&                      getClassTypeSpec(void);                                                                         //!< Get class type spec
        const TypeSpec&                             getTypeSpec(void) const;                                                                        //!< Get the type spec of the instance
        const MemberRules&                          getMemberRules(void) const;                                                                     //!< Get member rules (const)
//        void                                        printValue(std::ostream& o) const;                                                              //!< Print the general information on the function ('usage')
        
        
        // Distribution functions you have to override
        RevBayesCore::BranchRateJumpProcess*        createDistribution(void) const;
        
    protected:
        
        void                                        setConstMemberVariable(const std::string& name, const RbPtr<const Variable> &var);              //!< Set member variable
        
        
    private:
        
        RbPtr<const Variable>                       valueDistribution;
        RbPtr<const Variable>                       tree;
        RbPtr<const Variable>                       lambda;
        RbPtr<const Variable>                       instantaneousJumpProbability;
        
    };
    
}

#endif
