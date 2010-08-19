/**
 * @file
 * This file contains the declaration of VectorReal, a complex type
 * used to hold double vectors.
 *
 * @brief Declaration of VectorReal
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes core development team
 * @license GPL version 3
 * @version 1.0
 * @since 2009-12-04, version 1.0
 * @extends RbComplex
 *
 * $Id$
 */

#ifndef VectorReal_H
#define VectorReal_H

#include "VectorInteger.h"
#include "Container.h"

#include <iostream>
#include <string>
#include <vector>

class VectorReal : public Container {

    public:
                                    VectorReal(void) : Container() {}                          //!< Default constructor (empty vector)
                                    VectorReal(double x);                                      //!< Construct vector with one double x
	                                VectorReal(int n, double x);                               //!< Construct vector with n doubles x
	                                VectorReal(std::vector<double>& x);                        //!< Constructor from double vector

        // Basic utility functions
        virtual VectorReal*         clone(void) const;                                         //!< Clone object
        virtual bool                equals(const RbObject* obj) const;                         //!< Equals comparison
        virtual const VectorString& getClass(void) const;                                      //!< Get class vector
        virtual void                printValue(std::ostream& o) const;                         //!< Print value for user
        virtual std::string         toString(void) const;                                      //!< Complete info about object

        // Overloaded operators and built-in functions
        virtual double&             operator[](size_t i) { return value[i]; }                  //!< Index op allowing change
        const double&               operator[](size_t i) const { return value[i]; }            //!< Const index op
        void                        clear(void) { value.clear(); }                             //!< Clear
        virtual void                pop_back(void) { value.pop_back(); }                       //!< Drop element
        virtual void                push_back(double x) { value.push_back(x); }                //!< Append element to end
        virtual void                push_front(double x) { value.insert(value.begin(), x); }   //!< Add element in front
        void                        resize(size_t n) { resize(VectorInteger(int(n))); }        //!< Resize
        size_t                      size(void) const { return value.size(); }                  //!< Get size

        // Getter
        std::vector<double>&        getValue(void) { return value; }                           //!< Get value directly

        // Element access functions for parser
	    int                         getDim(void) const { return 1; }                           //!< Get subscript dimensions
        const std::string&          getElementType(void) const;                                //!< Get element type
        const RbObject*             getElement(const VectorInteger& index) const;              //!< Get element (read-only)
        const VectorInteger&        getLength(void) const;                                     //!< Get length in each dim
        virtual void                resize(const VectorInteger& len);                          //!< Resize
        virtual void                setElement(const VectorInteger& index, RbObject* val);     //!< Set element
        virtual void                setLength(const VectorInteger& len);                       //!< Set length in each dim

	protected:
        RbObject*                   convertTo(const std::string& type) const;                  //!< Convert to type
        bool                        isConvertibleTo(const std::string& type) const;            //!< Is convertible to type and dim?
	    std::vector<double>         value;                                                     //!< Vector of values
};

#endif


