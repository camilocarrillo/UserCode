import FWCore.ParameterSet.Config as cms


process = cms.Process("OwnParticles")


# have stareco use hlt digis
process.load("MuonTools.Configuration.HltMuonDigis_cff")
# have stareco use hlt segments (1)
process.load("MuonTools.Configuration.HltMuonSegments_cff")
# keep stareco from using rpcs
process.load("MuonTools.Configuration.StandAloneNoRpc_cff")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

#
process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")
#



process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "GR_R_52_V7::All"

process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

process.load("FWCore.MessageService.MessageLogger_cfi")

max = -1
 
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( max ))

process.normfilter = cms.EDFilter("HLTHighLevel",
                                      TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
                                      HLTPaths = cms.vstring("AlCa_RPCMuonNormalisation*"),
                                      eventSetupPathsKey = cms.string(''),
                                      andOr = cms.bool(True),
                                      throw = cms.bool(True)
                                  )


process.load("TriggerFilter.TriggerFilter.triggerFilter_cfi")
process.load("MuonTools.StandardSequences.RecoStandAloneMuon_cff")


process.load("DTandCSCSegmentsinTracks.DTandCSCSegmentsinTracks.dTandCSCSegmentsinTracks_cfi")
process.load("RecoLocalMuon.RPCRecHit.rpcPointProducerTrackSegments_cfi")




#process.load("RecoLocalMuon.RPCRecHit.rpcPointProducerThreeDetectors_cfi")
#process.load("RecoLocalMuon.RPCRecHit.rpcPointAnalyzer_cfi")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
#        '-input-'
#    'rfio:/castor/cern.ch/cms/store/data/Run2011A/RPCMonitor/RAW/v1/000/175/770/90D8BA85-18D9-E011-A3A3-001D09F242EA.root'
#    'rfio:/castor/cern.ch/cms/store/data/Run2011A/RPCMonitor/RAW/v1/000/163/286/C8135DBB-DA6C-E011-A1B5-003048F1C832.root'
#'//store/data/Run2011B/RPCMonitor/RAW/v1/000/179/308/4E17905E-A5FB-E011-92A0-003048D2C01E.root'
'rfio:/castor/cern.ch/cms/store/data/Run2011B/RPCMonitor/RAW/v1/000/180/250/FC7E6A53-FF02-E111-8B5A-003048F1110E.root'    
    #    'file:/tmp/jgomezca/source.root'
    
        )                            
                            )
process.options = cms.untracked.PSet(
            SkipEvent = cms.untracked.vstring('ProductNotFound')
                        )
process.museg = cms.EDAnalyzer("MuonSegmentEff",

                                   incldt = cms.untracked.bool(True),
                                   incldtMB4 = cms.untracked.bool(True),
                                   inclcsc = cms.untracked.bool(True),

                                   debug = cms.untracked.bool(False),
                                   inves = cms.untracked.bool(True),

                                   DuplicationCorrection = cms.untracked.int32(1),

                                   manualalignment = cms.untracked.bool(False),
                                   AliFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/endcap/CMSSW_3_0_0_pre10/src/DQM/RPCMonitorModule/data/Alignment69912.dat'),

                                   rangestrips = cms.untracked.double(4.),

                                 #  cscSegments = cms.untracked.InputTag('SelectedCscSegments'),
                                 #  dt4DSegments = cms.untracked.InputTag('SelectedDtSegments'),
                                   cscSegments = cms.untracked.InputTag('hltCscSegments'),
                                   dt4DSegments = cms.untracked.InputTag('hltDt4DSegments'),
                                   rpcRecHits = cms.InputTag("hltRpcRecHits"),

                               ##  cscSegments = cms.untracked.InputTag('cscSegments'),
                               ##  dt4DSegments = cms.untracked.InputTag('dt4DSegments'),
                               ##  rpcRecHits = cms.InputTag("rpcRecHits"),

                                   rpcDTPoints = cms.InputTag("rpcPointProducer","RPCDTExtrapolatedPoints"),
                                   rpcCSCPoints = cms.InputTag("rpcPointProducer","RPCCSCExtrapolatedPoints"),

                                   EffSaveRootFile = cms.untracked.bool(True),
                                   EffRootFileName = cms.untracked.string('numerator_denominatorTD.root'),
                                   EffSaveRootFileEventsInterval = cms.untracked.int32(100)
                               )




process.p = cms.Path(process.normfilter*process.triggerFilter*process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)
#process.p = cms.Path(process.normfilter*process.rpcPointProducer*process.museg)#*process.rpcMixedPointProducer)



process.DQM.collectorHost = ''
process.DQM.collectorPort = 9090
process.DQM.debug = False
