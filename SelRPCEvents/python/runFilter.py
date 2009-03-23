import FWCore.ParameterSet.Config as cms

process = cms.Process("SelRPCEvemts")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.selRPC = cms.EDFilter("SelRPCEvents")

#process.source = cms.Source("EmptySource")


process.source = cms.Source("PoolSource",
   fileNames = 
cms.untracked.vstring('/store/data/BeamCommissioning08/BeamHalo/RECO/v1/000/063/440/0058A079-D786-DD11-99CE-000423D952C0.root')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("selrpc")
    ),
    fileName = cms.untracked.string('/tmp/carrillo/RPCEvents.root')
)

process.selrpc = cms.Path(process.selRPC)
process.outpath = cms.EndPath(process.FEVT)
