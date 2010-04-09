import FWCore.ParameterSet.Config as cms

process = cms.Process("SelRPCEvemts")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

process.selRPC = cms.EDFilter("SelRPCEvents",
    eventsfile = cms.untracked.string('/afs/cern.ch/user/c/carrillo/scratch0/7TeVRaw/132440/runEventMonster.txt')
)

#process.source = cms.Source("EmptySource")


process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('//store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/C0A5D466-EC3B-DF11-BDF4-000423D9A2AE.root')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("selrpc")
    ),
    fileName = cms.untracked.string('filter132440.C0A5D466-EC3B-DF11-BDF4-000423D9A2AE.root')
)

process.selrpc = cms.Path(process.selRPC)
process.outpath = cms.EndPath(process.FEVT)
