import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/tmp/carrillo/AED6818A-F352-E011-A4C8-003048F118D4.root'
    )
)

process.demo = cms.EDAnalyzer('TriggerReader'
)


process.p = cms.Path(process.demo)
