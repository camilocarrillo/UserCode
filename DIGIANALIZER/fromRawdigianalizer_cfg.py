import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load('Configuration.StandardSequences.RawToDigi_Data_cff')

process.load('EventFilter.RPCRawToDigi.RPCFrontierCabling_cfi')

import EventFilter.RPCRawToDigi.rpcUnpacker_cfi

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    '/store/data/Commissioning10/Cosmics/RAW/v3/000/129/468/8E0140F1-8924-DF11-841B-0030487A3DE0.root'
    )
)

process.demo = cms.EDAnalyzer('DIGIANALIZER'
)

process.muonRPCDigis = EventFilter.RPCRawToDigi.rpcUnpacker_cfi.rpcunpacker.clone()

process.RawToDigi = cms.Sequence(process.muonRPCDigis*process.demo)
process.p = cms.Path(process.RawToDigi)
