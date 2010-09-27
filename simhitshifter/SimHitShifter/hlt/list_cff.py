import FWCore.ParameterSet.Config as cms
 
source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
    "file:/tmp/carrillo/PYTHIA6_Exotica_HSCP_stau200_cfg_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.root"
#   "file:/tmp/carrillo/PYTHIA6_Exotica_HSCP_stau200_cfg_py_GEN_SIM_SHIFT_DIGI_L1_DIGI2RAW_HLT.root"
   )
)
