//
// Created by Salieri on 2023/10/17.
//
#include "CbcFeasibilityBase.hpp"
#ifndef SOLVER_ENCAPSULATION_ZTEFEASIBILITYBASE_H
#define SOLVER_ENCAPSULATION_ZTEFEASIBILITYBASE_H


class ZteFeasibilityBase: public CbcFeasibilityBase {
public:
    /// Clone
    virtual ZteFeasibilityBase *clone() const
    {
        return new ZteFeasibilityBase(*this);
    }
};


#endif //SOLVER_ENCAPSULATION_ZTEFEASIBILITYBASE_H
