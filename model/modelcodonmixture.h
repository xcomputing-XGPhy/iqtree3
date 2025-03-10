//
//  modelcodonmixture.h
//  iqtree
//
//  Created by Minh Bui on 4/3/2025.
//

#ifndef modelcodonmixture_h
#define modelcodonmixture_h

#include <stdio.h>
#include "modelcodon.h"
#include "modelmixture.h"

/** Codon Mixture models like M2a, M3, M7, M8, notations following PAML package */
class ModelCodonMixture : public ModelMixture {
public:
    
    /**
        constructor
        @param model_name model name, e.g., CM2a, CM3
        @param freq state frequency type
        @param tree associated phylogenetic tree
    */
    ModelCodonMixture(string orig_model_name, string model_name, ModelsBlock *models_block,
            StateFreqType freq, string freq_params, PhyloTree *tree, bool optimize_weights);

    void initCodonMixture(int num_classes, string constraints, string model_name, ModelsBlock *models_block,
            StateFreqType freq, string freq_params, PhyloTree *tree);

    /**
     * destructor
     */
    virtual ~ModelCodonMixture();

private:

    bool link_kappa = true;
    
};

#endif /* modelcodonmixture_h */
