//
//  modelcodonmixture.cpp
//  iqtree
//
//  Created by Minh Bui on 4/3/2025.
//

#include "modelcodonmixture.h"


ModelCodonMixture::ModelCodonMixture(string orig_model_name, string model_name,
    ModelsBlock *models_block, StateFreqType freq, string freq_params,
    PhyloTree *tree, bool optimize_weights)
: ModelMarkov(tree), ModelMixture(tree)
{
    if (tree->aln->seq_type != SEQ_CODON)
        outError("Can't apply codon mixture model as sequence type is not codon");
    auto cmix_pos = orig_model_name.find("+CMIX");
    ASSERT(cmix_pos != string::npos);
    auto end_pos = orig_model_name.find_first_of("+*", cmix_pos+1);
    string cmix_type;
    if (end_pos == string::npos)
        cmix_type = orig_model_name.substr(cmix_pos+5);
    else
        cmix_type = orig_model_name.substr(cmix_pos+5, end_pos-cmix_pos-5);
    string model_list;
    if (cmix_type == "1a") {
        // M1a neural model with 2 classes
        model_list = model_name + "," + model_name + "{1.0/1.0}";
    } else if (cmix_type == "2a") {
        // M2a selection model with 3 classes
        model_list = model_name + "," + model_name + "{1.0/1.0}," + model_name;
    } else if (cmix_type == "3") {
        // M3 model with 3 classes with no constraint
        model_list = model_name + "," + model_name + "," + model_name;
    }    
    initMixture(orig_model_name, model_name, model_list, models_block,
                freq, freq_params, tree, optimize_weights);
}

void ModelCodonMixture::initCodonMixture(int num_classes, string constraints, string model_name,
    ModelsBlock *models_block, StateFreqType freq, string freq_params,
    PhyloTree *tree)
{
    int i;
    for (i = 0; i < num_classes; i++) {
        ModelCodon *model_codon =
            (ModelCodon*)createModel(model_name, models_block,
            freq_type, freq_params, tree);
        push_back(model_codon);
    }
    auto nmixtures = size();
    aligned_free(prop);
    prop = aligned_alloc<double>(nmixtures);
    for (i = 0; i < nmixtures; i++)
        prop[i] = 1.0/i;
}


ModelCodonMixture::~ModelCodonMixture()
{
    
}
