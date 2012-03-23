import FWCore.ParameterSet.Config as cms

process = cms.Process("DTcomparison2")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
# fileNames = cms.untracked.vstring('file:/tmp/carrillo/W2_Se4_St2_HighLumiBis.root')
# fileNames = cms.untracked.vstring('file:/tmp/carrillo/W2_Se4_St2_LowLumi.root')
# fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/j/jgomezca/NewRun1Container/_RPCMonitor_Run2011B-v1_RAW/180250/NewRun1Container-180250.E843AA1E-FD02-E111-81D3-BCAEC5329714.root')
  fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/j/jgomezca/OldRunContainer/_RPCMonitor_Run2011A-v1_RAW/163286/OldRunContainer-163286.14BFE702-DF6C-E011-8964-0030487C7E18.root')
)

process.DTcomparison = cms.EDFilter("DTcomparison",
  dt4DSegments = cms.InputTag("hltDt4DSegments"), 
# dt4DSegments = cms.InputTag("dTandCSCSegmentsinTracks",'SelectedDtSegments'),
  fileName =cms.untracked.string('LowLumi_AllSegments.root'),	
  Wheel = cms.untracked.int32(2),
  Sector = cms.untracked.int32(4),
  Station = cms.untracked.int32(1)
)



process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *',
	'keep *_dt4DSegments_*_*',
	'keep *_cscSegments_*_*',
	'keep *_muonRPCDigis_*_*',
	'keep *_rpcRecHits_*_*'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("compdt")
    ),

    fileName = cms.untracked.string('/tmp/carrillo/W2_Se4_St2_LowLumiBisBis.root')
)

process.compdt = cms.Path(process.DTcomparison)
process.outpath = cms.EndPath(process.FEVT)
