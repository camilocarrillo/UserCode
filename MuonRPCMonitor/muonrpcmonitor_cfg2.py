import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("DQMServices.Core.DQM_cfg")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("EmptySource")

process.demo = cms.EDAnalyzer('MuonRPCMonitor2',
#  tracks = cms.untracked.string('standAloneMuons'),
#  tracks = cms.untracked.string('standAloneSETMuons'), doesn't work
   tracks = cms.untracked.string('globalMuons'),
   rootFileName = cms.untracked.string('/tmp/carrillo/hscp.root'),
#  rootFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/scratch0/muonMonitor/PromptReco/PromptReco.root'),
   rootFileNameOut = cms.untracked.string('SummaryOut.root'),
   synchth = cms.untracked.double(0.01), #percentage of RPCRecHIts outside bx=0
   minIntegral = cms.untracked.double(10), #minimum number of hits asociated to a track in order to say something about the efficiency
   minMean = cms.untracked.double(0.01)	
)


process.p = cms.Path(process.demo)
