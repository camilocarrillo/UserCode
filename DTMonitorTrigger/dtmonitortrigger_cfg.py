import FWCore.ParameterSet.Config as cms
process = cms.Process("TriggerMonitor")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V1::All'

process.load("DQMServices.Core.DQM_cfg")
process.DQMStore = cms.Service("DQMStore")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      '/store/data/CRAFT09/RPCMonitor/RAW/v1/000/111/130/FAE8A846-8E8C-DE11-9937-003048D2BE12.root'
#      'file:/tmp/carrillo/FAE8A846-8E8C-DE11-9937-003048D2BE12.root'
    )
)

process.triggermon = cms.EDAnalyzer('DTMonitorTrigger',
   GMTInputTag = cms.InputTag("hltGtDigis"), 
   OutputName = cms.untracked.string('/tmp/carrillo/GMTOccupancyBit6.root'),

)

process.normfilter = cms.EDFilter("HLTHighLevel",
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring("AlCa_RPCMuonNoHits"),
    eventSetupPathsKey = cms.string(''),
    andOr = cms.bool(True),
    throw = cms.bool(True)
)

process.p = cms.Path(process.normfilter*process.triggermon)

process.DQM.collectorHost = ''
process.DQM.collectorPort = 9090
process.DQM.debug = False
