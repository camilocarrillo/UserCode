import FWCore.ParameterSet.Config as cms

#process = cms.Process("RPCPathChambFilter")

process = cms.Process("RPCSelectEventsForIlumination")
process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)

process.selRPC = cms.EDFilter("RPCSelectEventsForIlumination", 
  rpcDTPoints = cms.InputTag("rpcPointProducer","RPCDTExtrapolatedPoints"),
  rpcCSCPoints = cms.InputTag("rpcPointProducer","RPCCSCExtrapolatedPoints"),
)

process.source = cms.Source("PoolSource",
#   fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/c/carrillo/PointProducer/119090/119090.B294A2F1-72C7-DE11-9B7F-000423D991D4.root')
   fileNames = cms.untracked.vstring('file:/tmp/carrillo/point119090.root')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
       SelectEvents = cms.vstring("selrpc")
    ),
    fileName = cms.untracked.string('/tmp/carrillo/RE12.root')
)

process.selrpc = cms.Path(process.selRPC)
process.outpath = cms.EndPath(process.FEVT)

