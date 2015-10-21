#ifndef VIENNA_RNA_PACKAGE_DP_MATRICES_H
#define VIENNA_RNA_PACKAGE_DP_MATRICES_H

/**
 *  @file dp_matrices.h
 *
 *  @addtogroup   basic_data_structures  Basic Data Structures for Structure Prediction and Evaluation
 *  @{
 */

typedef struct  vrna_matrices_mfe vrna_mx_mfe_t;
typedef struct  vrna_matrices_pf  vrna_mx_pf_t;

#include <ViennaRNA/data_structures.h>

/* to use floats instead of doubles in pf_fold() comment next line */
#define LARGE_PF

#ifdef  LARGE_PF
#define FLT_OR_DBL double
#else
#define FLT_OR_DBL float
#endif

/**
 *  @brief  An enumerator that is used to specify the type of a polymorphic Dynamic Programming (DP)
 *  matrix data structure
 *  @see #vrna_mx_mfe_t, #vrna_mx_pf_t
 */
typedef enum {
  VRNA_MX_DEFAULT,  /**<  @brief  Default DP matrices */
  VRNA_MX_LOCAL,    /**<  @brief  DP matrices suitable for local structure prediction
                          @see    Lfold(), pfl_fold()
                    */
  VRNA_MX_2DFOLD    /**<  @brief  DP matrices suitable for distance class partitioned structure prediction
                          @see  vrna_TwoD_fold(), vrna_TwoD_pf_fold()
                    */
} vrna_mx_t;

/**
 *  @brief  Minimum Free Energy (MFE) Dynamic Programming (DP) matrices data structure required within the #vrna_fold_compound
 */
struct vrna_matrices_mfe {
  /** @name Common fields for MFE matrices
      @{
   */
  vrna_mx_t     type;
  unsigned int  length;    /**<  @brief  Length of the sequence, therefore an indicator of the size of the DP matrices */
  /**
      @}
   */

#if __STDC_VERSION__ >= 201112L
    /* C11 support for unnamed unions/structs */
  union {
    struct {
#endif
      /** @name Default DP matrices
          @note These data fields are available if
                @code vrna_mx_mfe_t.type == VRNA_MX_DEFAULT @endcode
        @{
       */
      int     *c;   /**<  @brief  Energy array, given that i-j pair */
      int     *f5;  /**<  @brief  Energy of 5' end */
      int     *f3;  /**<  @brief  Energy of 3' end */
      int     *fc;  /**<  @brief  Energy from i to cutpoint (and vice versa if i>cut) */
      int     *fML; /**<  @brief  Multi-loop auxiliary energy array */
      int     *fM1; /**<  @brief  Second ML array, only for unique multibrnach loop decomposition */
      int     *fM2; /**<  @brief  Energy for a multibranch loop region with exactly two stems, extending to 3' end */
      int     *ggg; /**<  @brief  Energies of g-quadruplexes */
      int     Fc;   /**<  @brief  Minimum Free Energy of entire circular RNA */
      int     FcH;
      int     FcI;
      int     FcM;
      /**
        @}
       */

#if __STDC_VERSION__ >= 201112L
    /* C11 support for unnamed unions/structs */
    };
    struct {
#endif
      /** @name Local Folding DP matrices
          @note These data fields are available if
                @code vrna_mx_mfe_t.type == VRNA_MX_LOCAL @endcode
        @{
       */
      int     **c_local;    /**<  @brief  Energy array, given that i-j pair */
      int     *f3_local;    /**<  @brief  Energy of 5' end */
      int     **fML_local;  /**<  @brief  Multi-loop auxiliary energy array */
      int     **ggg_local;  /**<  @brief  Energies of g-quadruplexes */
      /**
        @}
       */
#if __STDC_VERSION__ >= 201112L
    /* C11 support for unnamed unions/structs */
    };
    struct {
#endif

      /** @name Distance Class DP matrices
          @note These data fields are available if
                @code vrna_mx_mfe_t.type == VRNA_MX_2DFOLD @endcode
        @{
      */
      int             ***E_F5;
      int             **l_min_F5;
      int             **l_max_F5;
      int             *k_min_F5;
      int             *k_max_F5;

      int             ***E_F3;
      int             **l_min_F3;
      int             **l_max_F3;
      int             *k_min_F3;
      int             *k_max_F3;

      int             ***E_C;
      int             **l_min_C;
      int             **l_max_C;
      int             *k_min_C;
      int             *k_max_C;

      int             ***E_M;
      int             **l_min_M;
      int             **l_max_M;
      int             *k_min_M;
      int             *k_max_M;

      int             ***E_M1;
      int             **l_min_M1;
      int             **l_max_M1;
      int             *k_min_M1;
      int             *k_max_M1;

      int             ***E_M2;
      int             **l_min_M2;
      int             **l_max_M2;
      int             *k_min_M2;
      int             *k_max_M2;

      int             **E_Fc;
      int             *l_min_Fc;
      int             *l_max_Fc;
      int             k_min_Fc;
      int             k_max_Fc;

      int             **E_FcH;
      int             *l_min_FcH;
      int             *l_max_FcH;
      int             k_min_FcH;
      int             k_max_FcH;

      int             **E_FcI;
      int             *l_min_FcI;
      int             *l_max_FcI;
      int             k_min_FcI;
      int             k_max_FcI;

      int             **E_FcM;
      int             *l_min_FcM;
      int             *l_max_FcM;
      int             k_min_FcM;
      int             k_max_FcM;

      /* auxilary arrays for remaining set of coarse graining (k,l) > (k_max, l_max) */
      int             *E_F5_rem;
      int             *E_F3_rem;
      int             *E_C_rem;
      int             *E_M_rem;
      int             *E_M1_rem;
      int             *E_M2_rem;

      int             E_Fc_rem;
      int             E_FcH_rem;
      int             E_FcI_rem;
      int             E_FcM_rem;

#ifdef COUNT_STATES
      unsigned long   ***N_F5;
      unsigned long   ***N_C;
      unsigned long   ***N_M;
      unsigned long   ***N_M1;
#endif

      /**
        @}
       */

#if __STDC_VERSION__ >= 201112L
    /* C11 support for unnamed unions/structs */
    };
  };
#endif
};

/**
 *  @brief  Partition function (PF) Dynamic Programming (DP) matrices data structure required within the #vrna_fold_compound
 */
struct vrna_matrices_pf {
  /** @name Common fields for DP matrices
      @{
   */
  vrna_mx_t     type;
  unsigned int  length;

  /**
      @}
   */

#if __STDC_VERSION__ >= 201112L
    /* C11 support for unnamed unions/structs */
  union {
    struct {
#endif

  /** @name Default PF matrices
      @note These data fields are available if
            @code vrna_mx_pf_t.type == VRNA_MX_DEFAULT @endcode
      @{
   */
      FLT_OR_DBL  *q;
      FLT_OR_DBL  *qb;
      FLT_OR_DBL  *qm;
      FLT_OR_DBL  *qm1;
      FLT_OR_DBL  *probs;
      FLT_OR_DBL  *q1k;
      FLT_OR_DBL  *qln;
      FLT_OR_DBL  *G;

      FLT_OR_DBL  qo;
      FLT_OR_DBL  *qm2;
      FLT_OR_DBL  qho;
      FLT_OR_DBL  qio;
      FLT_OR_DBL  qmo;

      FLT_OR_DBL  *scale;
      FLT_OR_DBL  *expMLbase;
  /**
      @}
   */

#if __STDC_VERSION__ >= 201112L
    /* C11 support for unnamed unions/structs */
    };
    struct {
#endif

  /** @name Distance Class DP matrices
      @note These data fields are available if
            @code vrna_mx_pf_t.type == VRNA_MX_2DFOLD @endcode
      @{
   */
      FLT_OR_DBL      ***Q;
      int             **l_min_Q;
      int             **l_max_Q;
      int             *k_min_Q;
      int             *k_max_Q;


      FLT_OR_DBL      ***Q_B;
      int             **l_min_Q_B;
      int             **l_max_Q_B;
      int             *k_min_Q_B;
      int             *k_max_Q_B;

      FLT_OR_DBL      ***Q_M;
      int             **l_min_Q_M;
      int             **l_max_Q_M;
      int             *k_min_Q_M;
      int             *k_max_Q_M;

      FLT_OR_DBL      ***Q_M1;
      int             **l_min_Q_M1;
      int             **l_max_Q_M1;
      int             *k_min_Q_M1;
      int             *k_max_Q_M1;

      FLT_OR_DBL      ***Q_M2;
      int             **l_min_Q_M2;
      int             **l_max_Q_M2;
      int             *k_min_Q_M2;
      int             *k_max_Q_M2;

      FLT_OR_DBL      **Q_c;
      int             *l_min_Q_c;
      int             *l_max_Q_c;
      int             k_min_Q_c;
      int             k_max_Q_c;

      FLT_OR_DBL      **Q_cH;
      int             *l_min_Q_cH;
      int             *l_max_Q_cH;
      int             k_min_Q_cH;
      int             k_max_Q_cH;

      FLT_OR_DBL      **Q_cI;
      int             *l_min_Q_cI;
      int             *l_max_Q_cI;
      int             k_min_Q_cI;
      int             k_max_Q_cI;

      FLT_OR_DBL      **Q_cM;
      int             *l_min_Q_cM;
      int             *l_max_Q_cM;
      int             k_min_Q_cM;
      int             k_max_Q_cM;

      /* auxilary arrays for remaining set of coarse graining (k,l) > (k_max, l_max) */
      FLT_OR_DBL      *Q_rem;
      FLT_OR_DBL      *Q_B_rem;
      FLT_OR_DBL      *Q_M_rem;
      FLT_OR_DBL      *Q_M1_rem;
      FLT_OR_DBL      *Q_M2_rem;

      FLT_OR_DBL      Q_c_rem;
      FLT_OR_DBL      Q_cH_rem;
      FLT_OR_DBL      Q_cI_rem;
      FLT_OR_DBL      Q_cM_rem;
  /**
      @}
   */

#if __STDC_VERSION__ >= 201112L
    /* C11 support for unnamed unions/structs */
    };
  };
#endif
};

/**
 *  @brief  Add Dynamic Programming (DP) matrices (allocate memory)
 *
 *  This function adds DP matrices of a specific type to the provided
 *  #vrna_fold_compound, such that successive DP recursion can be applied.
 *  The function caller has to specify which type of DP matrix is requested,
 *  see #vrna_mx_t, and what kind of recursive algorithm will be applied
 *  later on, using the parameters type, and options, respectively. For the
 *  latter, Minimum free energy (MFE), and Partition function (PF)
 *  computations are distinguished. A third option that may be passed
 *  is #VRNA_OPTION_HYBRID, indicating that auxiliary DP arrays are
 *  required for RNA-RNA interaction prediction.
 *
 *  @note Usually, there is no need to call this function, since
 *  the constructors of #vrna_fold_compound are handling all the DP
 *  matrix memory allocation.
 *
 *  @see vrna_mx_mfe_add(), vrna_mx_pf_add(), vrna_get_fold_compound(),
 *  vrna_get_fold_compound_ali(), vrna_free_fold_compound(),
 *  vrna_free_pf_matrices(), vrna_free_mfe_matrices(), #vrna_mx_t,
 *  #VRNA_OPTION_MFE, #VRNA_OPTION_PF, #VRNA_OPTION_HYBRID, #VRNA_OPTION_EVAL_ONLY
 *
 *  @param  vc      The #vrna_fold_compound that holds pointers to the DP matrices
 *  @param  type    The type of DP matrices requested
 *  @param  options Option flags that specify the kind of DP matrices, such
 *                  as MFE or PF arrays, and auxiliary requirements
 *  @returns        1 if DP matrices were properly allocated and attached,
 *                  0 otherwise
 */
int vrna_mx_add(vrna_fold_compound *vc, vrna_mx_t type, unsigned int options);

int vrna_mx_mfe_add(vrna_fold_compound *vc, vrna_mx_t mx_type, unsigned int options);

int vrna_mx_pf_add(vrna_fold_compound *vc, vrna_mx_t mx_type, unsigned int options);

/**
 *  @brief  Free memory occupied by the Minimum Free Energy (MFE) Dynamic Programming (DP) matrices
 *
 *  @see vrna_get_fold_compound(), vrna_get_fold_compound_ali(), vrna_free_fold_compound(), vrna_free_pf_matrices()
 *
 *  @param  vc  The #vrna_fold_compound storing the MFE DP matrices that are to be erased from memory
 */
void vrna_free_mfe_matrices(vrna_fold_compound *vc);

/**
 *  @brief  Free memory occupied by the Partition Function (PF) Dynamic Programming (DP) matrices
 *
 *  @see vrna_get_fold_compound(), vrna_get_fold_compound_ali(), vrna_free_fold_compound(), vrna_free_mfe_matrices()
 *
 *  @param  vc  The #vrna_fold_compound storing the PF DP matrices that are to be erased from memory
 */
void vrna_free_pf_matrices(vrna_fold_compound *vc);

/**
 *  @}
 */

#endif
