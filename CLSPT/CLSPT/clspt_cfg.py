import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/tmp/carrillo/8E9FFE26-AC9A-E111-8273-003048F11114.root'
    )
)

process.demo = cms.EDAnalyzer('CLSPT',
   tracks = cms.untracked.string('globalMuons'),
   rpcRecHits = cms.InputTag("rpcRecHits"),
   rootFileName = cms.untracked.string('controlHistograms.root')
)


process.p = cms.Path(process.demo)
