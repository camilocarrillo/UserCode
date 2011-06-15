import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMHITSHIFTER")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT_98_1_yUz.root'
   )
)

process.load('simhitshifter.SimHitShifter.simhitshifter_cfi')

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/tmp/carrillo/myOutputFile.root')
)
  
process.p = cms.Path(process.theshifter)

process.e = cms.EndPath(process.out)
