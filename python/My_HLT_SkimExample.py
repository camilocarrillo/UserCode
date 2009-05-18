import FWCore.ParameterSet.Config as cms

process = cms.Process("My_HLT_Skim")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
   fileNames = 
cms.untracked.vstring('file:/tmp/carrillo/A4ABFCB0-D4CB-DD11-B688-001D0968F1FC.root')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *',
	'keep *_dt4DSegments_*_*',
	'keep *_cscSegments_*_*',
	'keep *_muonRPCDigis_*_*',
	'keep *_rpcRecHits_*_*'),
    fileName = cms.untracked.string('/tmp/carrillo/skim_A4ABFCB0-D4CB-DD11-B688-001D0968F1FC.root')
)

process.outpath = cms.EndPath(process.FEVT)
