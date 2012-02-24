import FWCore.ParameterSet.Config as cms

process = cms.Process("selDTEvents")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.selDTEvents = cms.EDFilter("DTSegEvents",
# dt4DSegments = cms.untracked.string('dt4DSegments'),
  dt4DSegments = cms.untracked.string('hltDt4DSegments'),
  Wheel = cms.untracked.int32(2),
  Sector = cms.untracked.int32(4),
  Station = cms.untracked.int32(1)
)

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/j/jgomezca/NewRun1Container/_RPCMonitor_Run2011B-v1_RAW/180250/NewRun1Container-180250.E843AA1E-FD02-E111-81D3-BCAEC5329714.root')
)


process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *',
	'keep *_dt4DSegments_*_*',
	'keep *_cscSegments_*_*',
	'keep *_muonRPCDigis_*_*',
	'keep *_rpcRecHits_*_*'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("seldt")
    ),

    fileName = cms.untracked.string('/tmp/carrillo/test.root')
)

process.seldt = cms.Path(process.selDTEvents)
process.outpath = cms.EndPath(process.FEVT)
