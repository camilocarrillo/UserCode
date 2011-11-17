import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMHITSHIFTER")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:/tmp/carrillo/EXO_HSCP_Stau100_Summer11ReproduceBX1_GEN_SIM.root'
   )
)

process.load('simhitshifter.SimHitShifter.simhitshifter_cfi')

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/tmp/carrillo/Stau100_GEN_SIM_SHIFT.root'),
    outputCommands = cms.untracked.vstring('keep *','keep *_g4SimHits_Muon*Hits_SIMHITSHIFTER','drop *_g4SimHits_Muon*Hits_HLT','drop *_simMuon*_*_*','drop CrossingFrame*_mix_*_*')
)
  
process.p = cms.Path(process.g4SimHits)

process.e = cms.EndPath(process.out)
