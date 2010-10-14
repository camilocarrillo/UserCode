import FWCore.ParameterSet.Config as cms

process = cms.Process("DROP")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/tmp/carrillo/PYTHIA6_Exotica_HSCP_stau200_cfg_py_GEN_SIM_SHIFT_DIGI_L1_DIGI2RAW_HLT.root'
    )
)

process.out = cms.OutputModule("PoolOutputModule",
  outputCommands = cms.untracked.vstring('keep *',
        'drop *_g4SimHits_MuonCSCHits_*',
        'drop *_g4SimHits_MuonRPCHits_*',
        'drop *_g4SimHits_MuonDTHits_*'),
  fileName = cms.untracked.string('/tmp/carrillo/afterdrop.root')
)
  
#process.p = cms.Path(process.rpcPointProducer)

process.e = cms.EndPath(process.out)

