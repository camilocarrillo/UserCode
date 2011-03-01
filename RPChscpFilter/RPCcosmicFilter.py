import FWCore.ParameterSet.Config as cms

process = cms.Process("ReSelRPChscpEvents")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.selRPC = cms.EDFilter("RPChscpFilter",
#  tracks = cms.untracked.string('standAloneMuons'),
#  tracks = cms.untracked.string('standAloneSETMuons'), doesn't work
   tracks = cms.untracked.string('globalMuons'),
   rpcRecHits = cms.InputTag("rpcRecHits"),
   MinRPCRecHits = cms.untracked.int32(2), #Hits in tracker track
   rootFileNameCal = cms.untracked.string('/afs/cern.ch/user/c/carrillo/tesis/CMSSW_3_8_4_patch4/src/MuonRPCMonitor/MuonRPCMonitor/hscp.root'),
   rootFileName = cms.untracked.string('/tmp/carrillo/controlHistograms.root'),
   synchth = cms.untracked.double(0.02), #percentage of RPCRecHIts outside bx=0
   minIntegral = cms.untracked.double(20), #minimum number of hits asociated to a track in order to say something about the efficiency
   minMean = cms.untracked.double(0.02)
)

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:/tmp/carrillo/antipv_46_1_VHP.root')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("selrpc")
    ),
    fileName = cms.untracked.string('/tmp/carrillo/filtering.root')
)

process.normfilter = cms.EDFilter("HLTHighLevel",
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring("AlCa_RPCMuonNormalisation"),
    eventSetupPathsKey = cms.string(''),
    andOr = cms.bool(True),
    throw = cms.bool(True)
)


process.hltpathfilter = cms.EDFilter("HLTHighLevel",
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring("HLT_Mu15_v1"),
    eventSetupPathsKey = cms.string(''),
    andOr = cms.bool(True),
    throw = cms.bool(True)
)


process.selrpc = cms.Path(process.hltpathfilter*process.selRPC)
process.outpath = cms.EndPath(process.FEVT)
