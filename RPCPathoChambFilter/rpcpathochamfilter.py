import FWCore.ParameterSet.Config as cms

process = cms.Process("RPCPathoChambFilter")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.selRPC = cms.EDFilter("RPCPathoChambFilter", 
  rangestrips = cms.untracked.double(4.),
  rpcRecHits = cms.InputTag('rpcRecHits'),
  rpcPoints = cms.InputTag("rpcPointProducer","rpcPoints")
)

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('file:/tmp/carrillo/output.root')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    fileName = cms.untracked.string('file:/tmp/carrillo/afterfilter.root')
)

process.selrpc = cms.Path(process.selRPC)
process.outpath = cms.EndPath(process.FEVT)
