﻿//
// Created by Salieri on 2023/10/16.
//
//#include "CbcModel.hpp"

//#include "ZteNode.h"
#include "ZteStrategy.h"
#include "ZteCglTreeProbingInfo.h"
#include "ZteFeasibilityBase.h"
//#include "ZteStatistics.h"
#include "ZteMessageHandler.h"
#include "ZteEventHandler.h"
//#include "ZteOsiSolverBranch.h"
#include "ZteBaseModel.h"
#include "ZteThread.h"
#include "CbcStatistics.hpp"



#ifndef SOLVER_ENCAPSULATION_ZTEMODEL_H
#define SOLVER_ENCAPSULATION_ZTEMODEL_H

// 移除"OsiSolverInterface.hpp"的"OsiSolverParameters.hpp"后加上
/*enum OsiHintStrength {
    *//** Ignore hint (default) *//*
    OsiHintIgnore = 0,
    *//** This means it is only a hint *//*
    OsiHintTry,
    *//** This means do hint if at all possible *//*
    OsiHintDo,
    *//** And this means throw an exception if not possible *//*
    OsiForceDo
};*/
/*enum CBC_Message {
    CBC_END_GOOD,
    CBC_MAXNODES,
    CBC_MAXTIME,
    CBC_MAXSOLS,
    CBC_EVENT,
    CBC_MAXITERS,
    CBC_SOLUTION,
    CBC_END_SOLUTION,
    CBC_SOLUTION2,
    CBC_END,
    CBC_INFEAS,
    CBC_STRONG,
    CBC_SOLINDIVIDUAL,
    CBC_INTEGERINCREMENT,
    CBC_STATUS,
    CBC_GAP,
    CBC_ROUNDING,
    CBC_TREE_SOL,
    CBC_ROOT,
    CBC_GENERATOR,
    CBC_BRANCH,
    CBC_STRONGSOL,
    CBC_NOINT,
    CBC_VUB_PASS,
    CBC_VUB_END,
    CBC_NOTFEAS1,
    CBC_NOTFEAS2,
    CBC_NOTFEAS3,
    CBC_CUTOFF_WARNING1,
    CBC_ITERATE_STRONG,
    CBC_PRIORITY,
    CBC_WARNING_STRONG,
    CBC_START_SUB,
    CBC_END_SUB,
    CBC_THREAD_STATS,
    CBC_CUTS_STATS,
    CBC_STRONG_STATS,
    CBC_UNBOUNDED,
    CBC_OTHER_STATS,
    CBC_HEURISTICS_OFF,
    CBC_STATUS2,
    CBC_FPUMP1,
    CBC_FPUMP2,
    CBC_STATUS3,
    CBC_OTHER_STATS2,
    CBC_RELAXED1,
    CBC_RELAXED2,
    CBC_RESTART,
    CBC_GENERAL,
    CBC_GENERAL_WARNING,
    CBC_ROOT_DETAIL,
#ifndef NO_FATHOM_PRINT
    CBC_FATHOM_CHANGE,
#endif
    CBC_DUMMY_END
};*/
/*enum OsiHintStrength {
    *//** Ignore hint (default) *//*
    OsiHintIgnore = 0,
    *//** This means it is only a hint *//*
    OsiHintTry,
    *//** This means do hint if at all possible *//*
    OsiHintDo,
    *//** And this means throw an exception if not possible *//*
    OsiForceDo
};*/
/*enum CBC_Message {
    CBC_END_GOOD,
    CBC_MAXNODES,
    CBC_MAXTIME,
    CBC_MAXSOLS,
    CBC_EVENT,
    CBC_MAXITERS,
    CBC_SOLUTION,
    CBC_END_SOLUTION,
    CBC_SOLUTION2,
    CBC_END,
    CBC_INFEAS,
    CBC_STRONG,
    CBC_SOLINDIVIDUAL,
    CBC_INTEGERINCREMENT,
    CBC_STATUS,
    CBC_GAP,
    CBC_ROUNDING,
    CBC_TREE_SOL,
    CBC_ROOT,
    CBC_GENERATOR,
    CBC_BRANCH,
    CBC_STRONGSOL,
    CBC_NOINT,
    CBC_VUB_PASS,
    CBC_VUB_END,
    CBC_NOTFEAS1,
    CBC_NOTFEAS2,
    CBC_NOTFEAS3,
    CBC_CUTOFF_WARNING1,
    CBC_ITERATE_STRONG,
    CBC_PRIORITY,
    CBC_WARNING_STRONG,
    CBC_START_SUB,
    CBC_END_SUB,
    CBC_THREAD_STATS,
    CBC_CUTS_STATS,
    CBC_STRONG_STATS,
    CBC_UNBOUNDED,
    CBC_OTHER_STATS,
    CBC_HEURISTICS_OFF,
    CBC_STATUS2,
    CBC_FPUMP1,
    CBC_FPUMP2,
    CBC_STATUS3,
    CBC_OTHER_STATS2,
    CBC_RELAXED1,
    CBC_RELAXED2,
    CBC_RESTART,
    CBC_GENERAL,
    CBC_GENERAL_WARNING,
    CBC_ROOT_DETAIL,
#ifndef NO_FATHOM_PRINT
    CBC_FATHOM_CHANGE,
#endif
    CBC_DUMMY_END
};*/


class ZteModel: public CbcModel{
//class ZteModel{
public:
    ZteModel();
    //ZteModel(const ZteOsiSolverInterface &);
    ZteModel(const OsiSolverInterface &);
    ZteModel(const ZteModel &rhs, bool cloneHandler = false);
    ~ZteModel();

    /// Get a double parameter
    virtual inline double getDblParam(CbcDblParam key) const
    {
        return dblParam_[key];
    }
    /// Returns solver - has current state
    virtual inline OsiSolverInterface *solver() const
    {
        return solver_;
    }
    /// Global cuts
    inline CbcRowCuts *globalCuts()
    {
        return &globalCuts_;
    }
    /*! \brief Get ownership of solver

        A return value of true means that CbcModel owns the solver and will
        take responsibility for deleting it when that becomes necessary.
      */
    inline bool modelOwnsSolver()
    {
        return ((ownership_ & 0x80000000) != 0);
    }
    /// Get the current parent model
    inline ZteModel *parentModel() const
    {
        return parentModel_;
    }
    /// Get time method
    inline bool useElapsedTime() const
    {
        return (moreSpecialOptions_ & 131072) != 0;
    }
    /// Number of rows in continuous (root) problem.
    virtual inline int numberRowsAtContinuous() const
    {
        return numberRowsAtContinuous_;
    }
    /// Get number of columns
    virtual inline int getNumCols() const
    {
        return solver_->getNumCols();
    }

    /// Get number of rows
    inline int getNumRows() const
    {
        return solver_->getNumRows();
    }
    /// Get the cutoff bound on the objective function - always as minimize
    virtual inline double getCutoff() const
    { //double value ;
        //solver_->getDblParam(OsiDualObjectiveLimit,value) ;
        //assert( dblParam_[CbcCurrentCutoff]== value * solver_->getObjSense());
        return dblParam_[CbcCurrentCutoff];
    }
    /// Return handler
    virtual inline ZteMessageHandler *messageHandler() const
    {
        return handler_;
    }
    /// Return messages
    virtual inline CoinMessages &messages()
    {
        return messages_;
    }
    /// Return pointer to messages
    virtual inline CoinMessages *messagesPointer()
    {
        return &messages_;
    }
    /// Get pointer to array[getNumCols()] of column lower bounds
    virtual inline const double *getColLower() const
    {
        return solver_->getColLower();
    }
    /// Get pointer to array[getNumCols()] of column upper bounds
    virtual inline const double *getColUpper() const
    {
        return solver_->getColUpper();
    }
    /// Get pointer to array[getNumCols()] (for speed) of column lower bounds
    virtual inline const double *getCbcColLower() const
    {
        return cbcColLower_;
    }
    /// Get pointer to array[getNumCols()] (for speed) of column upper bounds
    virtual inline const double *getCbcColUpper() const
    {
        return cbcColUpper_;
    }
    /// Get pointer to array[getNumRows()] (for speed) of row lower bounds
    virtual inline const double *getCbcRowLower() const
    {
        return cbcRowLower_;
    }
    /// Get pointer to array[getNumRows()] (for speed) of row upper bounds
    virtual inline const double *getCbcRowUpper() const
    {
        return cbcRowUpper_;
    }
    /// Set a double parameter
    inline bool setDblParam(CbcDblParam key, double value)
    {
        dblParam_[key] = value;
        return true;
    }
    /** Set the
  \link CbcModel::CbcMaximumSeconds maximum number of seconds \endlink
  desired.
*/
    inline bool setMaximumSeconds(double value)
    {
        return setDblParam(CbcMaximumSeconds, value);
    }
    /** Get the
  \link CbcModel::CbcCutoffIncrement  \endlink
  desired.
*/
    inline double getCutoffIncrement() const
    {
        return getDblParam(CbcCutoffIncrement);
    }
    inline double trueBestObjValue() const
    {
        return (moreSpecialOptions2_&67108864)==0 ? bestObjective_ : -bestObjective_;
    }
    /// Says if normal solver i.e. has well defined CoinPackedMatrix
    inline bool normalSolver() const
    {
        return (specialOptions_ & 16) == 0;
    }
    /** Get the
    \link CbcModel::CbcIntegerTolerance integrality tolerance \endlink
    */
    inline double getIntegerTolerance() const
    {
        return getDblParam(CbcIntegerTolerance);
    }
    /// Get pointer to array[getNumCols()] of objective function coefficients
    inline const double *getObjCoefficients() const
    {
        return solver_->getObjCoefficients();
    }
    /// Return objective function value with sign corrected
    virtual inline double trueObjValue(double value) const
    {
        return (moreSpecialOptions2_&67108864)==0 ? value : -value;
    }
    /*! \brief Retrieve a pointer to the event handler */
    inline ZteEventHandler *getEventHandler() const
    {
        return (eventHandler_);
    }
    /// Get pointer to array[getNumRows()] of row lower bounds
    inline const double *getRowLower() const
    {
        return solver_->getRowLower();
    }
    /// Get pointer to array[getNumRows()] of row upper bounds
    inline const double *getRowUpper() const
    {
        return solver_->getRowUpper();
    }
    /// Get an integer parameter
    inline int getIntParam(CbcIntParam key) const
    {
        return intParam_[key];
    }
    /// Get the \link CbcModel::CbcMaxNumNode maximum node limit \endlink
    inline int getMaximumNodes() const
    {
        return getIntParam(CbcMaxNumNode);
    }
    /// Set an integer parameter
    inline bool setIntParam(CbcIntParam key, int value)
    {
        intParam_[key] = value;
        return true;
    }
    /** Get the
      \link CbcModel::CbcMaximumSeconds maximum number of seconds \endlink
      desired.
    */
    inline double getMaximumSeconds() const
    {
        return getDblParam(CbcMaximumSeconds);
    }
    /** Get the
      \link CbcModel::CbcMaxNumSol maximum number of solutions \endlink
      desired.
    */
    inline int getMaximumSolutions() const
    {
        return getIntParam(CbcMaxNumSol);
    }
    /// Set the \link CbcModel::CbcMaxNumNode maximum node limit \endlink
    inline bool setMaximumNodes(int value)
    {
        return setIntParam(CbcMaxNumNode, value);
    }
    inline void incrementExtra(int nodes, int iterations, int fathoms = 1)
    {
        numberExtraNodes_ += nodes;
        numberExtraIterations_ += iterations;
        numberFathoms_ += fathoms;
    }
    /**
    Set special options
    0 bit (1) - check if cuts valid (if on debugger list)
    1 bit (2) - use current basis to check integer solution (rather than all slack)
    2 bit (4) - don't check integer solution (by solving LP)
    3 bit (8) - fast analyze
    4 bit (16) - non-linear model - so no well defined CoinPackedMatrix
    5 bit (32) - keep names
    6 bit (64) - try for dominated columns
    7 bit (128) - SOS type 1 but all declared integer
    8 bit (256) - Set to say solution just found, unset by doing cuts
    9 bit (512) - Try reduced model after 100 nodes
    10 bit (1024) - Switch on some heuristics even if seems unlikely
    11 bit (2048) - Mark as in small branch and bound
    12 bit (4096) - Funny cuts so do slow way (in some places)
    13 bit (8192) - Funny cuts so do slow way (in other places)
    14 bit (16384) - Use Cplex! for fathoming
    15 bit (32768) - Try reduced model after 0 nodes
    16 bit (65536) - Original model had integer bounds
    17 bit (131072) - Perturbation switched off
    18 bit (262144) - donor CbcModel
    19 bit (524288) - recipient CbcModel
    20 bit (1048576) - waiting for sub model to return
22 bit (4194304) - do not initialize random seed in solver (user has)
23 bit (8388608) - leave solver_ with cuts
24 bit (16777216) - just get feasible if no cutoff
25 bit (33554432) - feasibility pump after root cuts
26 bit (67108864) - child model but going for complete search
27 bit (134217728) - extra extra options
28 bit (268435456) - more of above2
*/
    inline void setSpecialOptions(int value)
    {
        specialOptions_ = value;
    }
    /// Get solver objective function value (as minimization)
    virtual inline double getSolverObjValue() const
    {
        return solver_->getObjValue() * solver_->getObjSense();
    }
    /** For testing infeasibilities - will point to
        currentSolution_ or solver-->getColSolution()
    */
    virtual inline const double *testSolution() const
    {
        return testSolution_;
    }
    /** \name Object manipulation routines

      See OsiObject for an explanation of `object' in the context of CbcModel.
    */
    //@{

    /// Get the number of objects
    virtual inline int numberObjects() const
    {
        return numberObjects_;
    }
    /// Get the hotstart solution
    virtual inline const double *hotstartSolution() const
    {
        return hotstartSolution_;
    }
    /// Get the hotstart priorities
    virtual inline const int *hotstartPriorities() const
    {
        return hotstartPriorities_;
    }
    /// Get solver characteristics
    virtual inline const OsiBabSolver *solverCharacteristics() const
    {
        return solverCharacteristics_;
    }
    /// Get the specified object
    virtual inline OsiObject *modifiableObject(int which) const
    {
        return object_[which];
    }
    /// Get special options
    virtual inline int specialOptions() const
    {
        return specialOptions_;
    }
    /// Get more special options
    virtual inline int moreSpecialOptions() const
    {
        return moreSpecialOptions_;
    }
    /// Get more special options2
    virtual inline int moreSpecialOptions2() const
    {
        return moreSpecialOptions2_;
    }
    /** Set more special options
        at present bottom 6 bits used for shadow price mode
        1024 for experimental hotstart
        2048,4096 breaking out of cuts
        8192 slowly increase minimum drop
        16384 gomory
	32768 more heuristics in sub trees
	65536 no cuts in preprocessing
        131072 Time limits elapsed
        18 bit (262144) - Perturb fathom nodes
        19 bit (524288) - No limit on fathom nodes
        20 bit (1048576) - Reduce sum of infeasibilities before cuts
        21 bit (2097152) - Reduce sum of infeasibilities after cuts
	22 bit (4194304) - Conflict analysis
	23 bit (8388608) - Conflict analysis - temporary bit
	24 bit (16777216) - Add cutoff as LP constraint (out)
	25 bit (33554432) - diving/reordering
	26 bit (67108864) - load global cuts from file
	27 bit (134217728) - append binding global cuts to file
	28 bit (268435456) - idiot branching
        29 bit (536870912) - don't make fake objective
	30 bit (1073741824) - Funny SOS or similar - be careful
    */
    virtual inline void setMoreSpecialOptions(int value)
    {
        moreSpecialOptions_ = value;
    }
    /** \name Problem feasibility checking */
    //@{
    // Feasibility functions (which may be overridden by inheritance)
    virtual inline CbcFeasibilityBase *problemFeasibility() const
    {
        return problemFeasibility_;
    }
    /** \name Row (constraint) and Column (variable) cut generation */
    //@{

    /** State of search
        0 - no solution
        1 - only heuristic solutions
        2 - branched to a solution
        3 - no solution but many nodes
    */
    virtual inline int stateOfSearch() const
    {
        return stateOfSearch_;
    }
    virtual inline void setStateOfSearch(int state)
    {
        stateOfSearch_ = state;
    }
    /** Get the maximum number of candidates to be evaluated for strong
      branching.
    */
    virtual inline int numberStrong() const
    {
        return numberStrong_;
    }
    /// Get the current branching decision method.
    virtual inline CbcBranchDecision *branchingMethod() const
    {
        return branchingMethod_;
    }
    /// Get how many Nodes it took to solve the problem (including those in complete fathoming B&B inside CLP).
    virtual inline int getNodeCount() const
    {
        return numberNodes_;
    }
    /// Get log level
    virtual inline int logLevel() const
    {
        return handler_->logLevel();
    }
    /** get the number of branches before pseudo costs believed
        in dynamic strong branching. */
    virtual inline int numberBeforeTrust() const
    {
        return numberBeforeTrust_;
    }
    /// Strategy worked out - mainly at root node for use by CbcNode
    virtual inline int searchStrategy() const
    {
        return searchStrategy_;
    }
    /// Get number of solutions
    virtual inline int getSolutionCount() const
    {
        return numberSolutions_;
    }
    /// Says whether all dynamic integers
    virtual inline bool allDynamic() const
    {
        return ((ownership_ & 0x40000000) != 0);
    }
    virtual inline int problemType() const
    {
        return problemType_;
    }
    /// Get best objective function value as minimization
    virtual inline double getMinimizationObjValue() const
    {
        return bestObjective_;
    }
    /** Return true if column is integer.
        Note: This function returns true if the the column
        is binary or a general integer.
    */
    virtual inline bool isInteger(int colIndex) const
    {
        return solver_->isInteger(colIndex);
    }
    /// Get how many iterations it took to solve the problem.
    virtual inline int getIterationCount() const
    {
        return numberIterations_;
    }
    /// Get the number of iterations done in strong branching.
    virtual inline int numberStrongIterations() const
    {
        return numberStrongIterations_;
    }
    /// Return strong info
    virtual inline const int *strongInfo() const
    {
        return strongInfo_;
    }
    /// Stong branching strategy
    virtual inline int strongStrategy() const
    {
        return strongStrategy_;
    }
    /// Number of integers in problem
    virtual inline int numberIntegers() const
    {
        return numberIntegers_;
    }
    // Integer variables
    virtual inline const int *integerVariable() const
    {
        return integerVariable_;
    }
    /// set last heuristic which found a solution
    virtual inline void setLastHeuristic(CbcHeuristic *last)
    {
        lastHeuristic_ = last;
    }
    /// Get the specified object
    virtual const inline OsiObject *object(int which) const
    {
        return object_[which];
    }
    /// Set strategy worked out - mainly at root node for use by CbcNode
    virtual inline void setSearchStrategy(int value)
    {
        searchStrategy_ = value;
    }
    /// Get best objective function value
    virtual inline double getObjValue() const
    {
        return bestObjective_ * solver_->getObjSense();
    }
    /** The best solution to the integer programming problem.

      The best solution to the integer programming problem found during
      the search. If no solution is found, the method returns null.
    */

    virtual inline double *bestSolution() const
    {
        return bestSolution_;
    }
    /// Get the current strategy
    virtual inline CbcStrategy *strategy() const
    {
        return strategy_;
    }
    /// Return the list of cuts initially collected for this subproblem
    virtual inline CbcCountRowCut **addedCuts() const
    {
        return addedCuts_;
    }
    /// Number of entries in the list returned by #addedCuts()
    virtual inline int currentNumberCuts() const
    {
        return currentNumberCuts_;
    }
    /// Tree method e.g. heap (which may be overridden by inheritance)
    virtual inline CbcTree *tree() const
    {
        return tree_;
    }
    /// Get a pointer to current node (be careful)
    virtual inline CbcNode *currentNode() const
    {
        return currentNode_;
    }
    /// Get useful temporary pointer
    virtual inline void *temporaryPointer() const
    {
        return temporaryPointer_;
    }
    /// Get number of heuristic solutions
    virtual inline int getNumberHeuristicSolutions() const
    {
        return numberHeuristicSolutions_;
    }
    /// Get current minimization objective function value
    virtual inline double getCurrentMinimizationObjValue() const
    {
        return dblParam_[CbcCurrentMinimizationObjectiveValue];
    }
    /// Value of objective at continuous
    virtual inline double getContinuousObjective() const
    {
        return originalContinuousObjective_;
    }
    /// Number of infeasibilities at continuous
    virtual inline int getContinuousInfeasibilities() const
    {
        return continuousInfeasibilities_;
    }
    /** \brief Set ownership of solver

      A parameter of false tells CbcModel it does not own the solver and
      should not delete it. Once you claim ownership of the solver, you're
      responsible for eventually deleting it. Note that CbcModel clones
      solvers with abandon.  Unless you have a deep understanding of the
      workings of CbcModel, the only time you want to claim ownership is when
      you're about to delete the CbcModel object but want the solver to
      continue to exist (as, for example, when branchAndBound has finished
      and you want to hang on to the answer).
    */
    virtual inline void setModelOwnsSolver(bool ourSolver)
    {
        ownership_ = ourSolver ? (ownership_ | 0x80000000) : (ownership_ & (~0x80000000));
    }
    /// Get the number of cut generators
    virtual inline int numberCutGenerators() const
    {
        return numberCutGenerators_;
    }
    ///Get the specified cut generator
    virtual inline CbcCutGenerator *cutGenerator(int i) const
    {
        return generator_[i];
    }
    /** Set the maximum number of cut passes at root node (default 20)
        Minimum drop can also be used for fine tuning */
    virtual inline void setMaximumCutPassesAtRoot(int value)
    {
        maximumCutPassesAtRoot_ = value;
    }
    /** Get the maximum number of cut passes at root node */
    virtual inline int getMaximumCutPassesAtRoot() const
    {
        return maximumCutPassesAtRoot_;
    }
    ///Get the specified heuristic
    virtual inline CbcHeuristic *heuristic(int i) const
    {
        return heuristic_[i];
    }
    /// Get the number of heuristics
    virtual inline int numberHeuristics() const
    {
        return numberHeuristics_;
    }
    /// Number of analyze iterations to do
    virtual inline void setNumberAnalyzeIterations(int number)
    {
        numberAnalyzeIterations_ = number;
    }
    virtual inline int numberAnalyzeIterations() const
    {
        return numberAnalyzeIterations_;
    }
    /** Return
        -2 if deterministic threaded and main thread
        -1 if deterministic threaded and serial thread
        0 if serial
        1 if opportunistic threaded
    */
    virtual inline int parallelMode() const
    {
        if (!numberThreads_) {
            if ((threadMode_ & 1) == 0)
                return 0;
            else
                return -1;
            return 0;
        } else {
            if ((threadMode_ & 1) == 0)
                return 1;
            else
                return -2;
        }
    }

    /// Pass in Message handler (not deleted at end)
    void passInMessageHandler(ZteMessageHandler *handler);

    /// Ensure attached objects point to this model.
    void synchronizeModel();

    /// Check original model before it gets messed up
    void checkModel();

    /**
    Flip direction of optimization on all models
    */
    void flipModel();

    /// Get how many Nodes it took to solve the problem.
    virtual int getNodeCount2() const
    {
        return numberNodes2_;
    }
    /// Set pointers for speed
    void setPointers(const OsiSolverInterface *solver);

    /** Add one generator - up to user to delete generators.
      howoften affects how generator is used. 0 or 1 means always,
      >1 means every that number of nodes.  Negative values have same
      meaning as positive but they may be switched off (-> -100) by code if
      not many cuts generated at continuous.  -99 is just done at root.
      Name is just for printout.
      If depth >0 overrides how often generator is called (if howOften==-1 or >0).
    */
    virtual void addCutGenerator(CglCutGenerator *generator,
                                 int howOften = 1, const char *name = NULL,
                                 bool normal = true, bool atSolution = false,
                                 bool infeasible = false, int howOftenInSub = -100,
                                 int whatDepth = -1, int whatDepthInSub = -1) ;

    /** If numberBeforeTrust >0 then we are going to use CbcBranchDynamic.
      Scan and convert CbcSimpleInteger objects
  */
    void convertToDynamic();

    /// Set numberBeforeTrust in all objects
    virtual void synchronizeNumberBeforeTrust(int type = 0) ;

    /** \brief Identify integer variables and create corresponding objects.

    Record integer variables and create an CbcSimpleInteger object for each
    one.
    If \p startAgain is true, a new scan is forced, overwriting any existing
    integer variable information.
    If type > 0 then 1==PseudoCost, 2 new ones low priority
    */
    virtual void findIntegers(bool startAgain, int type = 0) ;

    /// Make sure region there and optionally copy solution
    virtual void reserveCurrentSolution(const double *solution = NULL) ;

    /*! \brief Set cutoff bound on the objective function.

When using strict comparison, the bound is adjusted by a tolerance to
avoid accidentally cutting off the optimal solution.
*/
    virtual void setCutoff(double value) ;

    /// Generate an OsiBranchingInformation object
    virtual OsiBranchingInformation usefulInformation() const ;

    /// Make given column cut into a global cut
    void makeGlobalCut(const OsiColCut *cut);

    /// Check if a solution is really valid e.g. lazy constraints
    /// Returns true if ok or normal cuts (i.e. no atSolution ones)
    virtual bool reallyValid(OsiCuts *existingCuts = NULL) ;

    /** Call this to really test if a valid solution can be feasible
Solution is number columns in size.
If fixVariables true then bounds of continuous solver updated.
Returns objective value (worse than cutoff if not feasible)
Previously computed objective value is now passed in (in case user does not do solve)
virtual so user can override
*/
    virtual double checkSolution(double cutoff, double *solution,
                                 int fixVariables, double originalObjValue);

    /// Deals with event handler and solution
    ZteEventHandler::CbcAction dealWithEventHandler(ZteEventHandler::CbcEvent event,
                                                    double objValue,
                                                    const double *solution);

    /// Save a solution to saved list
    void saveExtraSolution(const double *solution, double objectiveValue);

    /// Save a solution to best and move current to saved
    void saveBestSolution(const double *solution, double objectiveValue);

    /// Current time since start of branchAndbound
    virtual double getCurrentSeconds() const ;

    /// Record a new incumbent solution and update objectiveValue
    virtual void setBestSolution(CBC_Message how,
                                 double &objectiveValue, const double *solution,
                                 int fixVariables = 0) ;

    /// Delete all object information (and just back to integers if true)
    void deleteObjects(bool findIntegers = true);

    // Analyze problem to find a minimum change in the objective function.
    void analyzeObjective();

    /// Adjust heuristics based on model
    void adjustHeuristics();

    /// Return true if maximum time reached
    bool maximumSecondsReached() const;

    /// Increases usedInSolution for nonzeros
    virtual void incrementUsed(const double *solution) ;

    /** Perform reduced cost fixing

        Fixes integer variables at their current value based on reduced cost
        penalties.  Returns number fixed
      */
    int reducedCostFix();

    /// Is optimality proven?
    bool isProvenOptimal() const;

    /// See if can stop on gap
    bool canStopOnGap() const;


    void setOptionalInteger(int index);

    /**
    Add additional integers.
    */
    void AddIntegers();

    /// Adds an update information object
    virtual void addUpdateInformation(const CbcObjectUpdateData &data) ;

    /** Return true if we want to do cuts
      If allowForTopOfTree zero then just does on multiples of depth
      if 1 then allows for doing at top of tree
      if 2 then says if cuts allowed anywhere apart from root
    */
    bool doCutsNow(int allowForTopOfTree) const;

    /** Set application data.

      This is a pointer that the application can store into and
      retrieve from the solver interface.
      This field is available for the application to optionally
      define and use.
      */
    void setApplicationData(void *appData);
    /// Get application data
    void *getApplicationData() const;

    /** Remove inactive cuts from the model

    An OsiSolverInterface is expected to maintain a valid basis, but not a
    valid solution, when loose cuts are deleted. Restoring a valid solution
    requires calling the solver to reoptimise. If it's certain the solution
    will not be required, set allowResolve to false to suppress
    reoptimisation.
    If saveCuts then slack cuts will be saved
    On input current cuts are cuts and newCuts
    on exit current cuts will be correct.  Returns number dropped
    */
    int takeOffCuts(OsiCuts &cuts,
                    bool allowResolve, OsiCuts *saveCuts,
                    int numberNewCuts = 0, const OsiRowCut **newCuts = NULL);

    /**
         Locks a thread if parallel so that stuff like cut pool
         can be updated and/or used.
      */
    void lockThread();
    /**
         Unlocks a thread if parallel to say cut pool stuff not needed
      */
    void unlockThread();

    /** Add in object information.

      Objects are cloned; the owner can delete the originals.
    */
    virtual void addObjects(int numberObjects, OsiObject **objects) ;
    /** Add in object information.

    Objects are cloned; the owner can delete the originals.
    */
    virtual void addObjects(int numberObjects, CbcObject **objects) ;

    /**
    Save copy of the model.
    */
    void saveModel(OsiSolverInterface *saveSolver, double *checkCutoffForRestart, bool *feasible);

    /** Pass in target solution and optional priorities.
    If priorities then >0 means only branch if incorrect
    while <0 means branch even if correct. +1 or -1 are
    highest priority */
    virtual void setHotstartSolution(const double *solution, const int *priorities = NULL) ;

    /**
 Clean model i.e. make SOS/integer variables exactly at bound if needed.
 Only if moreSpecialOptions2_ 15 bit set (32768) as there is a small
 overhead (more2 in standalone cbc).
 Fine tuning can be done in configure with -DCLEAN_INTEGER_VARIABLES
 and -DZERO_ODD_TOLERANCE=1.0e-nn
 If CLEAN_INTEGER_VARIABLES not defined then cleaning is only done for
 SOS variables.
 If ZERO_ODD_TOLERANCE not defined then 1.0e-14 used.  You can define as
 0.0 if you are paranoid.
 Returns number of variables forced out
 cleanVariables array will be used if exists
*/
    virtual int cleanBounds(OsiSolverInterface *solver, char *cleanVariables) ;

    /// Delete a node and possibly null out currentNode_
    virtual void deleteNode(CbcNode *node) ;

    /** Checks if one of the stopping criteria (max time, max nodes, ...) was reached */
    bool stoppingCriterionReached() const;

    /// Redo walkback arrays
    void redoWalkBack();

    /** Traverse the tree from node to root and prep the model

addCuts1() begins the job of prepping the model to match the current
subproblem. The model is stripped of all cuts, and the search tree is
traversed from node to root to determine the changes required. Appropriate
bounds changes are installed, a list of cuts is collected but not
installed, and an appropriate basis (minus the cuts, but big enough to
accommodate them) is constructed.

Returns true if new problem similar to old

    \todo addCuts1() is called in contexts where it's known in advance that
        all that's desired is to determine a list of cuts and do the
        bookkeeping (adjust the reference counts). The work of installing
        bounds and building a basis goes to waste.
    */
    virtual bool addCuts1(CbcNode *node, CoinWarmStartBasis *&lastws) ;

    /** Determine and install the active cuts that need to be added for
    the current subproblem

    The whole truth is a bit more complicated. The first action is a call to
    addCuts1(). addCuts() then sorts through the list, installs the tight
    cuts in the model, and does bookkeeping (adjusts reference counts).
    The basis returned from addCuts1() is adjusted accordingly.

    If it turns out that the node should really be fathomed by bound,
    addCuts() simply treats all the cuts as loose as it does the bookkeeping.

    */
    int addCuts(CbcNode *node, CoinWarmStartBasis *&lastws);

    /** Return pseudo costs
  If not all integers or not pseudo costs - returns all zero
  Length of arrays are numberIntegers() and entries
  correspond to integerVariable()[i]
  User must allocate arrays before call
*/
    void fillPseudoCosts(double *downCosts, double *upCosts,
                         int *priority = NULL,
                         int *numberDown = NULL, int *numberUp = NULL,
                         int *numberDownInfeasible = NULL,
                         int *numberUpInfeasible = NULL) const;


    /** Set objective value in a node.  This is separated out so that
     odd solvers can use.  It may look at extra information in
     solverCharacteriscs_ and will also use bound from parent node
    */
    void setObjectiveValue(CbcNode *thisNode, const CbcNode *parentNode) const;

    /// Sets up cleanVariables array (i.e. ones to be careful about)
    virtual char *setupCleanVariables() ;

    /// Fill in useful estimates
    virtual void pseudoShadow(int type);

    /** Get best possible objective function value.
      This is better of best possible left on tree
      and best solution found.
      If called from within branch and cut may be optimistic.
  */
    virtual double getBestPossibleObjValue() const ;

    /** Test the current solution for feasiblility.

    Scan all objects for indications of infeasibility. This is broken down
    into simple integer infeasibility (\p numberIntegerInfeasibilities)
    and all other reports of infeasibility (\p numberObjectInfeasibilities).
  */
    virtual bool feasibleSolution(int &numberIntegerInfeasibilities,
                                  int &numberObjectInfeasibilities) const ;

    /// Set log level
    virtual void setLogLevel(int value) ;

    /// Increment strong info
    virtual void incrementStrongInfo(int numberTimes, int numberIterations,
                                     int numberFixed, bool ifInfeasible) ;

    /** Set the maximum number of candidates to be evaluated for strong
    branching.

    A value of 0 disables strong branching.
  */
    virtual void setNumberStrong(int number) ;

    /** Set the number of branches before pseudo costs believed
      in dynamic strong branching.

    A value of 0 disables dynamic strong branching.
  */
    virtual void setNumberBeforeTrust(int number) ;

    /** Return an empty basis object of the specified size

    A useful utility when constructing a basis for a subproblem from scratch.
    The object returned will be of the requested capacity and appropriate for
    the solver attached to the model.
  */
    virtual CoinWarmStartBasis *getEmptyBasis(int ns = 0, int na = 0) const ;

    /** Assign a solver to the model (model assumes ownership)

    On return, \p solver will be NULL.
    If deleteSolver then current solver deleted (if model owned)

    \note Parameter settings in the outgoing solver are not inherited by
      the incoming solver.
  */
    virtual void assignSolver(OsiSolverInterface *&solver, bool deleteSolver = true) ;

    /*! \brief Add one heuristic - up to user to delete

      The name is just used for print messages.
    */
    virtual void addHeuristic(CbcHeuristic *generator, const char *name = NULL,
                              int before = -1) ;

    ///@name Solve methods
    //@{
    /** \brief Solve the initial LP relaxation

        Invoke the solver's %initialSolve() method.
      */
    void initialSolve();

    /** \brief Reoptimise an LP relaxation

    Invoke the solver's %resolve() method.
    whereFrom -
    0 - initial continuous
    1 - resolve on branch (before new cuts)
    2 - after new cuts
    3  - obsolete code or something modified problem in unexpected way
    10 - after strong branching has fixed variables at root
    11 - after strong branching has fixed variables in tree

    returns 1 feasible, 0 infeasible, -1 feasible but skip cuts
    */
    virtual int resolve(CbcNodeInfo *parent, int whereFrom,
                        double *saveSolution = NULL,
                        double *saveLower = NULL,
                        double *saveUpper = NULL) ;
    /// Encapsulates solver resolve
    virtual int resolve(OsiSolverInterface *solver) ;

    /** Do heuristics at root.
      0 - don't delete
      1 - delete
      2 - just delete - don't even use
    */
    void doHeuristicsAtRoot(int deleteHeuristicsAfterwards = 0);

    /** \brief Evaluate a subproblem using cutting planes and heuristics

    The method invokes a main loop which generates cuts, applies heuristics,
    and reoptimises using the solver's native %resolve() method.
    It returns true if the subproblem remains feasible at the end of the
    evaluation.
    */
    bool solveWithCuts(OsiCuts &cuts, int numberTries, CbcNode *node);

    /** Encapsulates choosing a variable -
      anyAction -2, infeasible (-1 round again), 0 done
    */
    int chooseBranch(CbcNode *&newNode, int numberPassesLeft,
                     CbcNode *oldNode, OsiCuts &cuts,
                     bool &resolved, CoinWarmStartBasis *lastws,
                     const double *lowerBefore, const double *upperBefore,
                     OsiSolverBranch *&branches);

    /// Go to dantzig pivot selection if easy problem (clp only)
    void goToDantzig(int numberNodes, ClpDualRowPivot *&savePivotMethod);

    /** Do one node - broken out for clarity?
      also for parallel (when baseModel!=this)
      Returns 1 if solution found
      node NULL on return if no branches left
      newNode NULL if no new node created
    */
    int doOneNode(ZteModel *baseModel, CbcNode *&node, CbcNode *&newNode);

    /// Invoke solver's built-in enumeration algorithm
    void branchAndBound(int doStatistics = 0);

private:

    //CbcModel preModel;

    /// Update size of whichGenerator
    void resizeWhichGenerator(int numberNow, int numberAfter);

    /** Generate one round of cuts - serial mode
    returns -
        0 - normal
        1 - must keep going
        2 - set numberTries to zero
        -1 - infeasible
      */
    int serialCuts(OsiCuts &cuts, CbcNode *node, OsiCuts &slackCuts, int lastNumberCuts);

    //CbcModel * createCbcModelForParam(ZteModel *zteModel);

    /// The solver associated with this model.
    OsiSolverInterface *solver_;
    /** Ownership of objects and other stuff

  0x80000000 model owns solver
  0x40000000 all variables CbcDynamicPseudoCost
*/
    unsigned int ownership_;
    /// A copy of the solver, taken at the continuous (root) node.
    OsiSolverInterface *continuousSolver_;

    /// A copy of the solver, taken at constructor or by saveReferenceSolver
    OsiSolverInterface *referenceSolver_;

    /// A copy of the solver, taken at a solution (lazy constraints)
    OsiSolverInterface *atSolutionSolver_;

    /// Parent model
    ZteModel *parentModel_;

    /// Array for double parameters
    double dblParam_[CbcLastDblParam];

    /// Array for integer parameters
    int intParam_[CbcLastIntParam];

    /** 0 - number times strong branching done, 1 - number fixed, 2 - number infeasible
      Second group of three is a snapshot at node [6] */
    int strongInfo_[7];

    /**
      For advanced applications you may wish to modify the behavior of Cbc
      e.g. if the solver is a NLP solver then you may not have an exact
      optimum solution at each step.  This gives characteristics - just for one BAB.
      For actually saving/restoring a solution you need the actual solver one.
    */
    OsiBabSolver *solverCharacteristics_;

    /// Strategy worked out - mainly at root node
    int searchStrategy_;
    /** Strategy for strong branching
	0 - normal
	when to do all fractional
	1 - root node
	2 - depth less than modifier
	4 - if objective == best possible
	6 - as 2+4
	when to do all including satisfied
	10 - root node etc.
	If >=100 then do when depth <= strategy/100 (otherwise 5)
     */
    int strongStrategy_;
    /// Number of iterations in strong branching
    int numberStrongIterations_;

    /// Current node so can be used elsewhere
    CbcNode *currentNode_;

    /**
      Special options
      0 bit (1) - check if cuts valid (if on debugger list)
      1 bit (2) - use current basis to check integer solution (rather than all slack)
      2 bit (4) - don't check integer solution (by solving LP)
      3 bit (8) - fast analyze
      4 bit (16) - non-linear model - so no well defined CoinPackedMatrix
      5 bit (32) - keep names
      6 bit (64) - try for dominated columns
      7 bit (128) - SOS type 1 but all declared integer
      8 bit (256) - Set to say solution just found, unset by doing cuts
      9 bit (512) - Try reduced model after 100 nodes
      10 bit (1024) - Switch on some heuristics even if seems unlikely
      11 bit (2048) - Mark as in small branch and bound
      12 bit (4096) - Funny cuts so do slow way (in some places)
      13 bit (8192) - Funny cuts so do slow way (in other places)
      14 bit (16384) - Use Cplex! for fathoming
      15 bit (32768) - Try reduced model after 0 nodes
      16 bit (65536) - Original model had integer bounds
      17 bit (131072) - Perturbation switched off
      18 bit (262144) - donor CbcModel
      19 bit (524288) - recipient CbcModel
      20 bit (1048576) - waiting for sub model to return
  22 bit (4194304) - do not initialize random seed in solver (user has)
  23 bit (8388608) - leave solver_ with cuts
  24 bit (16777216) - just get feasible if no cutoff
  */
    int specialOptions_;
    /** More special options
          at present bottom 6 bits used for shadow price mode
          1024 for experimental hotstart
          2048,4096 breaking out of cuts
          8192 slowly increase minimum drop
          16384 gomory
      32768 more heuristics in sub trees
      65536 no cuts in preprocessing
          131072 Time limits elapsed
          18 bit (262144) - Perturb fathom nodes
          19 bit (524288) - No limit on fathom nodes
          20 bit (1048576) - Reduce sum of infeasibilities before cuts
          21 bit (2097152) - Reduce sum of infeasibilities after cuts
      */
    int moreSpecialOptions_;
    /** More more special options
      0 bit (1) - find switching variables
      1 bit (2) - using fake objective until solution
      2 bit (4) - switching variables exist
      3 bit (8) - skip most of setBestSolution checks
      4 bit (16) - very lightweight preprocessing in smallB&B
      5 bit (32) - event handler needs to be cloned when parallel
      6 bit (64) - testing - use probing to make cliques
      7/8 bit (128) - try orbital branching (if nauty)
      9 bit (512) - branching on objective (later)
      10 bit (1024) - branching on constraints (later)
      11/12 bit 2048 - intermittent cuts
      13/14 bit 8192 - go to bitter end in strong branching (first time)
      15 bit 32768 - take care of very very small values for Integer/SOS variables
      16 bit 65536 - lazy constraints
          17 bit 131072 - fairly simple orbital
          18 bit 262144 - some statistics for fairly simple orbital
       19 bit 524288 - freeze problem at root cuts
       20 bit 1048576 - use ranging in CbcNode
      21 bit 2097152 - analyze changed priorities but were equal before
      22 bit 4194304 - ignore cutoff increment in multiple root solvers
      23 bit (8388608) - no crunch
      24 bit (67108864) - model has been flipped
      */
    int moreSpecialOptions2_;

    /// Tree
    CbcTree *tree_;
    /// Pointer to top of tree
    CbcFullNodeInfo *topOfTree_;

    /** \brief Integer and Clique and ... information

    \note The code assumes that the first objects on the list will be
      SimpleInteger objects for each integer variable, followed by
      Clique objects. Portions of the code that understand Clique objects
      will fail if they do not immediately follow the SimpleIntegers.
      Large chunks of the code will fail if the first objects are not
      SimpleInteger. As of 2003.08, SimpleIntegers and Cliques are the only
      objects.
  */
    OsiObject **object_;
    /// Total number of objects
    int numberObjects_;
    /// Now we may not own objects - just point to solver's objects
    bool ownObjects_;

    /// Original columns as created by integerPresolve or preprocessing
    int *originalColumns_;

    /// Strategy
    CbcStrategy *strategy_;

    /// Status of problem - 0 finished, 1 stopped, 2 difficulties
    int status_;
    /** Secondary status of problem
          -1 unset (status_ will also be -1)
          0 search completed with solution
          1 linear relaxation not feasible (or worse than cutoff)
          2 stopped on gap
          3 stopped on nodes
          4 stopped on time
          5 stopped on user event
          6 stopped on solutions
       */
    int secondaryStatus_;

    /** Value of objective before root node cuts added
  */
    double originalContinuousObjective_;

    /// Number of integers in problem
    int numberIntegers_;
    /// Number of rows at continuous
    int numberRowsAtContinuous_;

    /// Array holding the incumbent (best) solution.
    double *bestSolution_;
    /** Array holding the current solution.

    This array is used more as a temporary.
  */
    double *currentSolution_;
    /** For testing infeasibilities - will point to
      currentSolution_ or solver-->getColSolution()
  */
    mutable const double *testSolution_;

    /// Indices of integer variables
    int *integerVariable_;
    /// Whether of not integer
    char *integerInfo_;
    /// Holds solution at continuous (after cuts)
    double *continuousSolution_;

    /// Array marked whenever a solution is found if non-zero
    int *usedInSolution_;

    /// Whether event happened
    mutable bool eventHappened_;

    /// Probing info
    ZteCglTreeProbingInfo *probingInfo_;

    /// User node comparison function
    CbcCompareBase *nodeCompare_;
    /// User feasibility function (see CbcFeasibleBase.hpp)
    CbcFeasibilityBase *problemFeasibility_;

    /// Hotstart solution
    double *hotstartSolution_;
    /// Hotstart priorities
    int *hotstartPriorities_;

    /// Maximum number of cuts
    int maximumNumberCuts_;
    /** Current phase (so heuristics etc etc can find out).
      0 - initial solve
      1 - solve with cuts at root
      2 - solve with cuts
      3 - other e.g. strong branching
      4 - trying to validate a solution
      5 - at end of search
  */
    int phase_;
    /// Number of entries in #addedCuts_
    int currentNumberCuts_;

    /** \brief The number of branches before pseudo costs believed
         in dynamic strong branching.

    A value of 0 is  off.
  */
    int numberBeforeTrust_;

    /// Preferred way of branching
    int preferredWay_;

    /** Value of objective at continuous
      (Well actually after initial round of cuts)
  */
    double continuousObjective_;

    /** keepNamesPreproc
 *  if variables names will be preserved in the pre-processed problem
 *  (usefull in callbacks)
 **/
    bool keepNamesPreproc;

    /// Number of analyze iterations to do
    int numberAnalyzeIterations_;

    /// Cumulative number of solves
    int numberSolves_;

    /// Number of cut generators
    int numberCutGenerators_;
    // Cut generators
    CbcCutGenerator **generator_;
    // Cut generators before any changes
    CbcCutGenerator **virginGenerator_;

    /// Number of saved solutions
    int numberSavedSolutions_;

    /** Maximum number of candidates to consider for strong branching.
    To disable strong branching, set this to 0.
  */
    int numberStrong_;

    /**
     -1 - cutoff as constraint not activated
     -2 - waiting to activate
     >=0 - activated
   */
    int cutoffRowNumber_;

    /// Best objective
    double bestObjective_;
    /// Best possible objective
    double bestPossibleObjective_;
    /// Sum of Changes to objective by first solve
    double sumChangeObjective1_;
    /// Sum of Changes to objective by subsequent solves
    double sumChangeObjective2_;

    /// Variable selection function
    CbcBranchDecision *branchingMethod_;

    /// Number of heuristics
    int numberHeuristics_;
    /// Heuristic solvers
    CbcHeuristic **heuristic_;
    /// Pointer to heuristic solver which found last solution (or NULL)
    CbcHeuristic *lastHeuristic_;

    /// Depth for fast nodes
    int fastNodeDepth_;

    /**
     Parallel
     0 - off
     1 - testing
     2-99 threads
     other special meanings
  */
    int numberThreads_;

    /// Number of solutions
    int numberSolutions_;

    /// Number of heuristic solutions
    int numberHeuristicSolutions_;

    /** State of search
      0 - no solution
      1 - only heuristic solutions
      2 - branched to a solution
      3 - no solution but many nodes
  */
    int stateOfSearch_;

    /// Maximum number of cuts (for whichGenerator_)
    int maximumWhich_;
    /// Maximum number of rows
    int maximumRows_;

    /// Which cut generator generated this cut
    int *whichGenerator_;
    /// Maximum number of statistics
    int maximumStatistics_;
    /// statistics
    CbcStatistics **statistics_;
    /// Maximum depth reached
    int maximumDepthActual_;
    /// Number of reduced cost fixings
    double numberDJFixed_;

    /// Current depth
    int currentDepth_;
    /** Current limit on search tree depth

    The allocated size of #walkback_. Increased as needed.
  */
    int maximumDepth_;
    /** Array used to assemble the path between a node and the search tree root

    The array is resized when necessary. #maximumDepth_  is the current
    allocated size.
  */
    CbcNodeInfo **walkback_;
    CbcNodeInfo **lastNodeInfo_;
    const OsiRowCut **lastCut_;
    int lastDepth_;
    /** The list of cuts initially collected for this subproblem

    When the subproblem at this node is rebuilt, a set of cuts is collected
    for inclusion in the constraint system. If any of these cuts are
    subsequently removed because they have become loose, the corresponding
    entry is set to NULL.
    */
    CbcCountRowCut **addedCuts_;
    /** A pointer to a row cut which will be added instead of normal branching.
      After use it should be set to NULL.
  */
    OsiRowCut *nextRowCut_;

    int *lastNumberCuts_;
    int lastNumberCuts2_;
    int maximumCuts_;

    /// Number of old active cuts
    int numberOldActiveCuts_;
    /// Number of new cuts
    int numberNewCuts_;

    /// Cumulative number of nodes
    int numberNodes_;
    /** Cumulative number of nodes for statistics.
      Must fix to match up
  */
    int numberNodes2_;
    /// Cumulative number of iterations
    int numberIterations_;

    /// Multiple root tries
    int multipleRootTries_;

    /// Random seed
    unsigned int randomSeed_;

    /// Whether stopping on gap
    bool stoppedOnGap_;

    /// Global cuts
    CbcRowCuts globalCuts_;
    /// Global conflict cuts
    CbcRowCuts *globalConflictCuts_;

    /// Thread specific random number generator
    mutable CoinThreadRandom randomNumberGenerator_;

    /// Number of infeasibilities at continuous
    int continuousInfeasibilities_;
    /// Maximum number of cut passes at root
    int maximumCutPassesAtRoot_;

    int numberFixedAtRoot_;
    /// Number fixed by analyze so far
    int numberFixedNow_;

    /// Arrays with analysis results
    double *analyzeResults_;

    /// Number of long strong goes
    int numberLongStrong_;

    /// Last time when progress message was printed
    double lastSecPrintProgress_;
    /// Print frequency in nodes
    int printFrequency_;
    /// Print frequency in time
    double secsPrintFrequency_;

    /// Number of extra nodes in fast lp
    int numberExtraNodes_;
    /// Number of extra iterations in fast lp
    int numberExtraIterations_;
    /// Maximum number of iterations (designed to be used in heuristics)
    int maximumNumberIterations_;

    /// Number of times any subtree stopped on nodes, time etc
    int numberStoppedSubTrees_;

    /// Work basis for temporary use
    CoinWarmStartBasis workingBasis_;

    /// Stored row cuts for donor/recipient CbcModel
    CglStored *storedRowCuts_;

    /** thread mode
      always use numberThreads for branching
      1 set then deterministic
      2 set then use numberThreads for root cuts
      4 set then use numberThreads in root mini branch and bound
      default is 0
  */
    int threadMode_;

    /// Message handler
    ZteMessageHandler *handler_;
    /// Flag to say if default handler (so delete)
    bool defaultHandler_;

    /// Messages
    CoinMessages messages_;
    /// Coin messages
    CoinMessages coinMessages_;
    /// Event handler
    ZteEventHandler *eventHandler_;

    /** Whether to automatically do presolve before branch and bound.
  0 - no
  1 - ordinary presolve
  2 - integer presolve (dodgy)
*/
    /// Pointer to array[getNumCols()] (for speed) of column lower bounds
    const double *cbcColLower_;
    /// Pointer to array[getNumCols()] (for speed) of column upper bounds
    const double *cbcColUpper_;
    /// Pointer to array[getNumRows()] (for speed) of row lower bounds
    const double *cbcRowLower_;
    /// Pointer to array[getNumRows()] (for speed) of row upper bounds
    const double *cbcRowUpper_;
    /// Pointer to array[getNumCols()] (for speed) of primal solution vector
    const double *cbcColSolution_;
    /// Pointer to array[getNumRows()] (for speed) of dual prices
    const double *cbcRowPrice_;
    /// Get a pointer to array[getNumCols()] (for speed) of reduced costs
    const double *cbcReducedCost_;
    /// Pointer to array[getNumRows()] (for speed) of row activity levels.
    const double *cbcRowActivity_;

    /// Anything with priority >= this can be treated as continuous
    int continuousPriority_;

    /** Warm start object produced by heuristic or strong branching

  If get a valid integer solution outside branch and bound then it can take
  a reasonable time to solve LP which produces clean solution.  If this object has
  any size then it will be used in solve.
*/
    CoinWarmStartBasis bestSolutionBasis_;

    // if values of integer variables should be rounded before saving,
    // default false
    bool roundIntVars_;

    /// Last node where a better feasible solution was found
    int lastNodeImprovingFeasSol_;
    /// Last time when a better feasible solution was found
    double lastTimeImprovingFeasSol_;

    /// Maximum number of saved solutions
    int maximumSavedSolutions_;

    /// Arrays holding other solutions.
    double **savedSolutions_;

    /** Problem type as set by user or found by analysis.  This will be extended
      0 - not known
      1 - Set partitioning <=
      2 - Set partitioning ==
      3 - Set covering
    */
    int problemType_;

    /// Current cut pass number
    int currentPassNumber_;

    /// Number of nodes infeasible by normal branching (before cuts)
    int numberInfeasibleNodes_;

    /// Minimum degradation in objective value to continue cut generation
    double minimumDrop_;

    /// How often to scan global cuts
    int howOftenGlobalScan_;

    /** Number of times global cuts violated.  When global cut pool then this
  should be kept for each cut and type of cut */
    int numberGlobalViolations_;

    /// Whether to force a resolve after takeOffCuts
    bool resolveAfterTakeOffCuts_;

    /// At which depths to do cuts
    int whenCuts_;

    /// Maximum number of cut passes
    int maximumCutPasses_;

    /// Number of outstanding update information items
    int numberUpdateItems_;
    /// Maximum number of outstanding update information items
    int maximumNumberUpdateItems_;
    /// Update items
    CbcObjectUpdateData *updateItems_;

    /// Pointer to user-defined data structure
    void *appData_;

    /// Number of times fast lp entered
    int numberFathoms_;

    /// Thread stuff for master
    ZteBaseModel *master_;
    /// Pointer to masterthread
    ZteThread *masterThread_;

    /** Pointer to an empty warm start object

    It turns out to be useful to have this available as a base from
    which to build custom warm start objects. This is typed as CoinWarmStart
    rather than CoinWarmStartBasis to allow for the possibility that a
    client might want to apply a solver that doesn't use a basis-based warm
    start. See getEmptyBasis for an example of how this field can be used.
  */
    mutable CoinWarmStart *emptyWarmStart_;

    /// Useful temporary pointer
    void *temporaryPointer_;
};

#endif //SOLVER_ENCAPSULATION_ZTEMODEL_H
