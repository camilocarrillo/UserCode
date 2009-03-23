import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
#   fileNames = cms.untracked.vstring('//store/data/Commissioning08/Cosmics/RECO/v1/000/070/402/ACDB9133-C5AE-DD11-9F83-001D09F2983F.root')
#   fileNames = cms.untracked.vstring('file:/tmp/carrillo/ACDB9133-C5AE-DD11-9F83-001D09F2983F.root')
   fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/c/carrillo/skimByChamber/70195_W2_S4_St1_B.root')
)

process.demo = cms.EDAnalyzer('ErrorSegments'
)


process.p = cms.Path(process.demo)
