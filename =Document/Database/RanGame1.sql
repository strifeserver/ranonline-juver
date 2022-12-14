USE [RanGame1]
GO
/****** Object:  Table [dbo].[ChaFriend]    Script Date: 10/25/2015 16:51:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaFriend](
	[ChaFriendNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaP] [int] NOT NULL,
	[ChaS] [int] NOT NULL,
	[ChaFlag] [int] NOT NULL CONSTRAINT [DF_ChaFriend_ChaFlag]  DEFAULT ((1)),
 CONSTRAINT [PK_ChaFriend] PRIMARY KEY CLUSTERED 
(
	[ChaFriendNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Attendance]    Script Date: 10/25/2015 16:51:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Attendance](
	[UserNum] [int] NOT NULL,
	[RewardCount] [int] NULL,
	[DaysCount] [int] NULL,
	[AttendDate] [datetime] NULL,
 CONSTRAINT [PK_Attendance] PRIMARY KEY CLUSTERED 
(
	[UserNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GuildRegion]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GuildRegion](
	[RegionID] [int] NOT NULL,
	[GuNum] [int] NOT NULL CONSTRAINT [DF_GuildRegion_GuNum]  DEFAULT ((0)),
	[RegionTax] [float] NOT NULL CONSTRAINT [DF_GuildRegion_RegionTax]  DEFAULT ((0.0)),
 CONSTRAINT [PK_GuildRegion] PRIMARY KEY CLUSTERED 
(
	[RegionID] ASC,
	[GuNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GuildInfo]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[GuildInfo](
	[GuNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaNum] [int] NOT NULL CONSTRAINT [DF_GuildInfo_ChaNum]  DEFAULT ((0)),
	[GuDeputy] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuDeputy]  DEFAULT ((0)),
	[GuName] [varchar](33) NOT NULL CONSTRAINT [DF_GuildInfo_GuName]  DEFAULT (''),
	[GuNotice] [varchar](401) NOT NULL CONSTRAINT [DF_GuildInfo_GuNotice]  DEFAULT (''),
	[GuRank] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuRank]  DEFAULT ((0)),
	[GuMoney] [money] NOT NULL CONSTRAINT [DF_GuildInfo_GuMoney]  DEFAULT ((0)),
	[GuIncomeMoney] [money] NOT NULL CONSTRAINT [DF_GuildInfo_GuIncomeMoney]  DEFAULT ((0)),
	[GuMarkVer] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuMarkVer]  DEFAULT ((0)),
	[GuExpire] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuExpire]  DEFAULT ((0)),
	[GuMakeTime] [datetime] NOT NULL CONSTRAINT [DF_GuildInfo_GuMakeTime]  DEFAULT (getdate()),
	[GuExpireTime] [datetime] NOT NULL CONSTRAINT [DF_GuildInfo_GuExpireTime]  DEFAULT ('1970-02-01'),
	[GuAllianceSec] [datetime] NOT NULL CONSTRAINT [DF_GuildInfo_GuAllianceSec]  DEFAULT ('1970-02-01'),
	[GuAllianceDis] [datetime] NOT NULL CONSTRAINT [DF_GuildInfo_GuAllianceDis]  DEFAULT ('1970-02-01'),
	[GuMarkImage] [image] NOT NULL CONSTRAINT [DF_GuildInfo_GuMarkImage]  DEFAULT (''),
	[GuStorage] [image] NOT NULL CONSTRAINT [DF_GuildInfo_GuStorage]  DEFAULT (''),
	[GuAuthorityTime] [datetime] NOT NULL CONSTRAINT [DF_GuildInfo_GuAuthorityTime_1]  DEFAULT ('1970-02-01'),
	[GuAllianceBattleLose] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuAllianceBattleLose_1]  DEFAULT ((0)),
	[GuAllianceBattleDraw] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuAllianceBattleDraw_1]  DEFAULT ((0)),
	[GuAllianceBattleWin] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuAllianceBattleWin_1]  DEFAULT ((0)),
	[GuBattleLastTime] [datetime] NOT NULL CONSTRAINT [DF_GuildInfo_GuBattleLastTime_1]  DEFAULT ('1970-02-01'),
	[GuBattleLose] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuBattleLose_1]  DEFAULT ((0)),
	[GuBattleDraw] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuBattleDraw_1]  DEFAULT ((0)),
	[GuBattleWin] [int] NOT NULL CONSTRAINT [DF_GuildInfo_GuBattleWin_1]  DEFAULT ((0)),
 CONSTRAINT [PK_GuildInfo] PRIMARY KEY CLUSTERED 
(
	[GuNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY],
 CONSTRAINT [IX_GuildInfo_Name] UNIQUE NONCLUSTERED 
(
	[GuName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[GuildBattle]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GuildBattle](
	[GuBattleNum] [int] IDENTITY(1,1) NOT NULL,
	[GuSNum] [int] NULL CONSTRAINT [DF_GuildBattle_GuSNum]  DEFAULT ((0)),
	[GuPNum] [int] NULL CONSTRAINT [DF_GuildBattle_GuPNum]  DEFAULT ((0)),
	[GuAlliance] [int] NULL CONSTRAINT [DF_GuildBattle_GuAlliance]  DEFAULT ((0)),
	[GuFlag] [int] NULL CONSTRAINT [DF_GuildBattle_GuFlag]  DEFAULT ((0)),
	[GuKillNum] [int] NULL CONSTRAINT [DF_GuildBattle_GuKillNum]  DEFAULT ((0)),
	[GuDeathNum] [int] NULL,
	[GuBattleStartDate] [datetime] NULL CONSTRAINT [DF_GuildBattle_GuBattleStartDate]  DEFAULT (getdate()),
	[GuBattleEndDate] [datetime] NULL CONSTRAINT [DF_GuildBattle_GuBattleEndDate]  DEFAULT (getdate())
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GuildAlliance]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GuildAlliance](
	[GuNumP] [int] NOT NULL CONSTRAINT [DF_GuildAlliance_GuNumP]  DEFAULT ((0)),
	[GuNumS] [int] NOT NULL CONSTRAINT [DF_GuildAlliance_GuNumS]  DEFAULT ((0)),
 CONSTRAINT [PK_GuildAlliance] PRIMARY KEY CLUSTERED 
(
	[GuNumP] ASC,
	[GuNumS] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[VehicleInfo]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[VehicleInfo](
	[VehicleUniqueNum] [int] IDENTITY(1,1) NOT NULL,
	[VehicleNum] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleNum]  DEFAULT ((0)),
	[VehicleName] [varchar](20) NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleName]  DEFAULT (''),
	[VehicleChaNum] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleChaNum]  DEFAULT ((0)),
	[VehicleType] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleType]  DEFAULT ((0)),
	[VehicleCardMID] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleCardMID]  DEFAULT ((0)),
	[VehicleCardSID] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleCardSID]  DEFAULT ((0)),
	[VehicleBattery] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleBattery]  DEFAULT ((1000)),
	[VehicleBooster] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleBooster]  DEFAULT ((0)),
	[VehicleDeleted] [int] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleDeleted]  DEFAULT ((0)),
	[VehicleCreateDate] [datetime] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleCreateDate]  DEFAULT (getdate()),
	[VehicleDeletedDate] [datetime] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleDeletedDate]  DEFAULT (getdate()),
	[VehiclePutOnItems] [image] NOT NULL CONSTRAINT [DF_VehicleInfo_VehiclePutOnItems]  DEFAULT (''),
	[VehicleColor] [image] NOT NULL CONSTRAINT [DF_VehicleInfo_VehicleColor]  DEFAULT (''),
 CONSTRAINT [PK_VehicleInfo] PRIMARY KEY CLUSTERED 
(
	[VehicleUniqueNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UserInven]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserInven](
	[UserInvenNum] [int] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[SGNum] [int] NOT NULL,
	[ChaStorage2] [datetime] NOT NULL CONSTRAINT [DF_UserInven_ChaStorage2]  DEFAULT ('1970-02-01'),
	[ChaStorage3] [datetime] NOT NULL CONSTRAINT [DF_UserInven_ChaStorage3]  DEFAULT ('1970-02-01'),
	[ChaStorage4] [datetime] NOT NULL CONSTRAINT [DF_UserInven_ChaStorage4]  DEFAULT ('1970-02-01'),
	[UserMoney] [money] NOT NULL,
	[UserInven] [image] NULL,
 CONSTRAINT [IDX_InvenUserNum] PRIMARY KEY CLUSTERED 
(
	[UserInvenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY],
 CONSTRAINT [IX_UserInven] UNIQUE NONCLUSTERED 
(
	[UserNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
/****** Object:  Table [dbo].[PetTypeFlag]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PetTypeFlag](
	[PetType] [int] NOT NULL,
	[PetName] [varchar](20) NOT NULL,
 CONSTRAINT [PK_PetTypeFlag] PRIMARY KEY CLUSTERED 
(
	[PetType] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PetStyleFlag]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PetStyleFlag](
	[PetStyle] [int] NOT NULL,
	[PetStyleName] [varchar](2) NOT NULL,
 CONSTRAINT [PK_PetStyleFlag] PRIMARY KEY CLUSTERED 
(
	[PetStyle] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PetInven]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PetInven](
	[PetInvenNum] [int] IDENTITY(1,1) NOT NULL,
	[PetNum] [int] NOT NULL CONSTRAINT [DF_PetInven_PetNum]  DEFAULT ((0)),
	[PetInvenType] [int] NOT NULL CONSTRAINT [DF_PetInven_PetInvenType]  DEFAULT ((0)),
	[PetInvenMID] [int] NOT NULL CONSTRAINT [DF_PetInven_PetInvenMID]  DEFAULT ((0)),
	[PetInvenSID] [int] NOT NULL CONSTRAINT [DF_PetInven_PetInvenSID]  DEFAULT ((0)),
	[PetInvenCMID] [int] NOT NULL CONSTRAINT [DF_PetInven_PetInvenCMID]  DEFAULT ((0)),
	[PetInvenCSID] [int] NOT NULL CONSTRAINT [DF_PetInven_PetInvenCSID]  DEFAULT ((0)),
	[PetInvenAvailable] [int] NOT NULL CONSTRAINT [DF_PetInven_PetInvenAvailable]  DEFAULT ((0)),
	[PetInvenUpdateDate] [datetime] NOT NULL CONSTRAINT [DF_PetInven_PetInvenUpdateDate]  DEFAULT (getdate()),
	[PetChaNum] [int] NOT NULL CONSTRAINT [DF_PetInven_PetChaNum]  DEFAULT ('0'),
 CONSTRAINT [PK_PetInven] PRIMARY KEY CLUSTERED 
(
	[PetInvenNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PetInfo]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PetInfo](
	[PetNum] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetNum]  DEFAULT ((0)),
	[PetName] [varchar](20) NOT NULL CONSTRAINT [DF_PetInfo_PetName]  DEFAULT (''),
	[PetChaNum] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetChaNum]  DEFAULT ((0)),
	[PetType] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetType]  DEFAULT ((0)),
	[PetMID] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetMID]  DEFAULT ((0)),
	[PetSID] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetSID]  DEFAULT ((0)),
	[PetStyle] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetStyle]  DEFAULT ((0)),
	[PetColor] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetColor]  DEFAULT ((0)),
	[PetFull] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetFull]  DEFAULT ((1000)),
	[PetDualSkill] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetDualSkill]  DEFAULT ((0)),
	[PetDeleted] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetDeleted]  DEFAULT ((0)),
	[PetCreateDate] [datetime] NOT NULL CONSTRAINT [DF_PetInfo_PetCreateDate]  DEFAULT (getdate()),
	[PetDeletedDate] [datetime] NOT NULL CONSTRAINT [DF_PetInfo_PetDeletedDate]  DEFAULT (getdate()),
	[PetPutOnItems] [image] NOT NULL CONSTRAINT [DF_PetInfo_PetPutOnItems]  DEFAULT (''),
	[PetCardMID] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetCardMID]  DEFAULT ((0)),
	[PetCardSID] [int] NOT NULL CONSTRAINT [DF_PetInfo_PetCardSID]  DEFAULT ((0)),
	[PetUniqueNum] [int] IDENTITY(1,1) NOT NULL,
	[PetSkinStartDate] [datetime] NULL CONSTRAINT [DF_PetInfo_PetSkinStartDate]  DEFAULT (getdate()),
	[PetSkinTime] [datetime] NULL CONSTRAINT [DF_PetInfo_PetSkinTime]  DEFAULT (getdate()),
	[PetSkinScale] [int] NULL CONSTRAINT [DF_PetInfo_PetSkinScale]  DEFAULT ((0)),
	[PetSkinMID] [int] NULL CONSTRAINT [DF_PetInfo_PetSkinMID]  DEFAULT ((0)),
	[PetSkinSID] [int] NULL CONSTRAINT [DF_PetInfo_PetSkinSID]  DEFAULT ((0)),
 CONSTRAINT [PK_PetInfo] PRIMARY KEY CLUSTERED 
(
	[PetUniqueNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogPartyMatch]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogPartyMatch](
	[SGNum] [int] NOT NULL CONSTRAINT [DF_LogPartyMatch_SGNum]  DEFAULT ((0)),
	[SvrNum] [int] NOT NULL CONSTRAINT [DF_LogPartyMatch_SvrNum]  DEFAULT ((0)),
	[Win] [int] NOT NULL CONSTRAINT [DF_LogPartyMatch_Win]  DEFAULT ((0)),
	[Lost] [int] NOT NULL CONSTRAINT [DF_LogPartyMatch_Lost]  DEFAULT ((0)),
	[MatchTime] [datetime] NOT NULL CONSTRAINT [DF_LogPartyMatch_MatchTime]  DEFAULT (getdate()),
 CONSTRAINT [PK_LogPartyMatch] PRIMARY KEY CLUSTERED 
(
	[MatchTime] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ChaNameInfo]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ChaNameInfo](
	[ChaNameNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaNum] [int] NOT NULL CONSTRAINT [DF_ChaNameInfo_ChaNum]  DEFAULT ((0)),
	[ChaName] [varchar](33) NOT NULL CONSTRAINT [DF_ChaNameInfo_ChaName]  DEFAULT (''),
 CONSTRAINT [PK_ChaNameInfo] PRIMARY KEY NONCLUSTERED 
(
	[ChaNameNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ChaInfo]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ChaInfo](
	[ChaNum] [int] IDENTITY(1,1) NOT NULL,
	[SGNum] [int] NULL CONSTRAINT [DF_ChaInfo_SGNum]  DEFAULT ((0)),
	[UserNum] [int] NOT NULL,
	[GuNum] [int] NULL CONSTRAINT [DF_ChaInfo_GuNum]  DEFAULT ((0)),
	[GuPosition] [int] NOT NULL CONSTRAINT [DF_ChaInfo_GuPosition]  DEFAULT ((0)),
	[ChaName] [varchar](33) NOT NULL,
	[ChaGuName] [varchar](33) NOT NULL CONSTRAINT [DF_ChaInfo_ChaGuName]  DEFAULT (''),
	[ChaTribe] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaTribe]  DEFAULT ((0)),
	[ChaClass] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaClass]  DEFAULT ((0)),
	[ChaSchool] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSchool]  DEFAULT ((0)),
	[ChaHair] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaHair]  DEFAULT ((0)),
	[ChaFace] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaFace]  DEFAULT ((0)),
	[ChaLiving] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaLiving]  DEFAULT ((0)),
	[ChaLevel] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaLevel]  DEFAULT ((0)),
	[ChaReborn] [int] NOT NULL CONSTRAINT [DF__ChaInfo__ChaRebo__2EDAF651]  DEFAULT ((0)),
	[ChaMoney] [money] NOT NULL CONSTRAINT [DF_ChaInfo_ChaMoney]  DEFAULT ((0)),
	[ChaPower] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaPower]  DEFAULT ((0)),
	[ChaDex] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaDex]  DEFAULT ((0)),
	[ChaSpirit] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSpirit]  DEFAULT ((0)),
	[ChaStrong] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStrong]  DEFAULT ((0)),
	[ChaStrength] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStrength]  DEFAULT ((0)),
	[ChaIntel] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaIntel]  DEFAULT ((0)),
	[ChaStRemain] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStRemain]  DEFAULT ((0)),
	[ChaExp] [money] NOT NULL CONSTRAINT [DF_ChaInfo_ChaExp]  DEFAULT ((0)),
	[ChaViewRange] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaViewRange]  DEFAULT ((0)),
	[ChaHP] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaHP]  DEFAULT ((0)),
	[ChaMP] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaMP]  DEFAULT ((0)),
	[ChaSP] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSP]  DEFAULT ((0)),
	[ChaCP] [bigint] NOT NULL CONSTRAINT [DF_ChaInfo_ChaCP]  DEFAULT ((0)),
	[ChaStartMap] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStartMap]  DEFAULT ((0)),
	[ChaStartGate] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStartGate]  DEFAULT ((0)),
	[ChaPosX] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaPosX]  DEFAULT ((0)),
	[ChaPosY] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaPosY]  DEFAULT ((0)),
	[ChaPosZ] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaPosZ]  DEFAULT ((0)),
	[ChaSaveMap] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSaveMap]  DEFAULT ((-1)),
	[ChaSavePosX] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSavePosX]  DEFAULT ((0)),
	[ChaSavePosY] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSavePosY]  DEFAULT ((0)),
	[ChaSavePosZ] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSavePosZ]  DEFAULT ((0)),
	[ChaReturnMap] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaReturnMap]  DEFAULT ((-1)),
	[ChaReturnPosX] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaReturnPosX]  DEFAULT ((0)),
	[ChaReturnPosY] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaReturnPosY]  DEFAULT ((0)),
	[ChaReturnPosZ] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaReturnPosZ]  DEFAULT ((0)),
	[ChaBright] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaBright]  DEFAULT ((0)),
	[ChaAttackP] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaAttackP]  DEFAULT ((0)),
	[ChaDefenseP] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaDefenseP]  DEFAULT ((0)),
	[ChaFightA] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaFightA]  DEFAULT ((0)),
	[ChaShootA] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaShootA]  DEFAULT ((0)),
	[ChaPK] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaPK]  DEFAULT ((0)),
	[ChaSkillPoint] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaSkillPoint]  DEFAULT ((0)),
	[ChaInvenLine] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaInvenLine]  DEFAULT ((0)),
	[ChaDeleted] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaDeleted]  DEFAULT ((0)),
	[ChaOnline] [int] NOT NULL CONSTRAINT [DF_ChaInfo_ChaOnline]  DEFAULT ((0)),
	[ChaCreateDate] [datetime] NOT NULL CONSTRAINT [DF_ChaInfo_ChaCreateDate]  DEFAULT (getdate()),
	[ChaDeletedDate] [datetime] NOT NULL CONSTRAINT [DF_ChaInfo_ChaDeletedDate]  DEFAULT (getdate()),
	[ChaStorage2] [datetime] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStorage2]  DEFAULT ('1970-02-01'),
	[ChaStorage3] [datetime] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStorage3]  DEFAULT ('1970-02-01'),
	[ChaStorage4] [datetime] NOT NULL CONSTRAINT [DF_ChaInfo_ChaStorage4]  DEFAULT ('1970-02-01'),
	[ChaGuSecede] [datetime] NOT NULL CONSTRAINT [DF_ChaInfo_ChaGuSecede]  DEFAULT ('1970-02-01'),
	[ChaQuest] [image] NULL,
	[ChaSkills] [image] NULL,
	[ChaSkillSlot] [image] NULL,
	[ChaActionSlot] [image] NULL,
	[ChaPutOnItems] [image] NULL,
	[ChaInven] [image] NULL,
	[ChaCoolTime] [image] NULL,
	[ChaSex] [int] NULL,
	[ChaHairStyle] [int] NULL,
	[ChaHairColor] [int] NULL,
	[ChaReExp] [float] NOT NULL CONSTRAINT [DF_ChaInfo_ChaReExp]  DEFAULT ((0)),
	[ChaSpSID] [int] NULL CONSTRAINT [DF_ChaInfo_ChaSpSID_1]  DEFAULT ((0)),
	[ChaSpMID] [int] NULL CONSTRAINT [DF_ChaInfo_ChaSpMID_1]  DEFAULT ((0)),
	[ChaPersonalMap] [image] NULL,
 CONSTRAINT [PK_ChaInfo] PRIMARY KEY CLUSTERED 
(
	[ChaNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ChaFriendBackup]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaFriendBackup](
	[ChaFriendNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaP] [int] NOT NULL,
	[ChaS] [int] NOT NULL,
	[ChaFlag] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[DeleteChaFriend]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[DeleteChaFriend]
	@nChaP int,
	@nChaS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	DELETE FROM ChaFriend 
	WHERE ChaP=@nChaP AND ChaS=@nChaS	
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  View [dbo].[viewChaFriend]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO
-------------------------------------------------------------------------------
-- view_ChaFriend
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewChaFriend]
AS
SELECT TOP 100 PERCENT dbo.ChaFriend.ChaP, dbo.ChaFriend.ChaS, 
       dbo.ChaInfo.ChaName, dbo.ChaFriend.ChaFlag
FROM   dbo.ChaFriend INNER JOIN
       dbo.ChaInfo ON dbo.ChaFriend.ChaS = dbo.ChaInfo.ChaNum
ORDER BY dbo.ChaInfo.ChaName
GO
/****** Object:  StoredProcedure [dbo].[InsertChaFriend]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[InsertChaFriend]
	@nChaP int,
	@nChaS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	INSERT INTO ChaFriend (ChaP, ChaS) 
	VALUES(@nChaP, @nChaS)
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaFriend]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[UpdateChaFriend]
	@nChaP int,
	@nChaS int,
	@nFlag int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE ChaFriend
	SET ChaFlag=@nFlag
	WHERE ChaP=@nChaP AND ChaS=@nChaS
	
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_UserAttendLog]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_UserAttendLog]
@UserNum		int
AS
/*
Created by PrinceOfPersia
August 8, 2011
*/

DECLARE @EXIST int ;
		
SET NOCOUNT ON;

SELECT @EXIST =  COUNT(1) FROM Attendance (NOLOCK) WHERE UserNum = @UserNum;

IF 	@EXIST = 0
BEGIN
	SELECT NULL, 0, 0 
	RETURN;	
END;

SELECT AttendDate,DaysCount, RewardCount
FROM Attendance	WHERE UserNum = @UserNum;

SET NOCOUNT OFF;
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertAttendLog]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_InsertAttendLog]
	@UserNum	int,
	@nCount	int,
	@nReward int,
	@nReturn	int OUTPUT
AS	

/*
Created by PrinceOfPersia
August 8, 2011
*/

DECLARE @exist int;
		
SET NOCOUNT ON;

SET @nReturn = -1;

BEGIN TRAN

SELECT @EXIST =  COUNT(1) FROM Attendance(NOLOCK) WHERE UserNum = @UserNum;

IF @EXIST= 0
BEGIN
	INSERT INTO Attendance(
	UserNum,
	DaysCount,
	RewardCount,
	AttendDate
	)
	VALUES (
	@UserNum,
	1,
	@nReward,
	GETDATE()
	)		
END
ELSE
BEGIN 
	UPDATE Attendance 
	SET DaysCount = @nCount, 
	RewardCount = @nReward,
	AttendDate = GETDATE()
	WHERE UserNum = @UserNum;
END

IF @@ERROR = 0 
	BEGIN 
		COMMIT TRAN;
		SET @nReturn = 0;
	END

SET NOCOUNT OFF;
RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_guild_region]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE Procedure [dbo].[sp_delete_guild_region]
	@RegionID int,
    @GuNum int,
	@nReturn int	OUTPUT	
AS
	DECLARE @error_var int, 
		    @rowcount_var int

	SET NOCOUNT ON
		 
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0
	
	IF EXISTS(SELECT * FROM GuildRegion WHERE RegionID=@RegionID AND GuNum=@GuNum)
	BEGIN -- ??? ??? ????
		UPDATE GuildRegion 
		SET GuNum=0, RegionTax=0 
		WHERE RegionID=@RegionID
		
		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
		IF @error_var <> 0 OR @rowcount_var = 0 -- ????
		BEGIN
			SET @nReturn = 0
			SET NOCOUNT OFF
			RETURN @nReturn
		END
	END
	ELSE -- ??? ??? ???? ??? ??
	BEGIN
		SET @nReturn = 0
		SET NOCOUNT OFF			
		RETURN @nReturn		
	END
	
	SET @nReturn = 1
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_add_guild_region]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE Procedure [dbo].[sp_add_guild_region]
	@RegionID int,
    @GuNum    int,
    @RegionTax float,
	@nReturn int	OUTPUT	
AS
	DECLARE @error_var int, 
		    @rowcount_var int
		    
	SET NOCOUNT ON
		 
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0
	
	IF EXISTS(SELECT * FROM GuildRegion WHERE RegionID=@RegionID)
	BEGIN -- ??? ????
		UPDATE GuildRegion 
		SET GuNum=@GuNum, RegionTax=@RegionTax 
		WHERE RegionID=@RegionID
		
		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
		IF @error_var <> 0 OR @rowcount_var = 0 -- ????
		BEGIN
			SET @nReturn = 0
			SET NOCOUNT OFF
			RETURN @nReturn
		END
	END
	ELSE
	BEGIN
		INSERT INTO GuildRegion (RegionID, GuNum, RegionTax) 
		VALUES (@RegionID, @GuNum, @RegionTax)
		
		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
		IF @error_var <> 0 OR @rowcount_var = 0 -- ????
		BEGIN
			SET @nReturn = 0
			SET NOCOUNT OFF
			RETURN @nReturn
		END
	END
	SET @nReturn = 1
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_create_guild]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_create_guild]
    @ChaNum  int,
	@GuName  char(33),
	@nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int, -- ?? ??         
         @error_var int, 
		 @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    -----------------------------------------------------------------
    -- ?? ?? ???? ???? ??? ????.  
	SELECT @nGuNum=GuNum 
	FROM GuildInfo 
	WHERE ChaNum=@ChaNum
      
	IF @nGuNum <> 0 -- ??? ??, ???????
	BEGIN 
		SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	
	-----------------------------------------------------------------
    -- ??? ??? ????.
    INSERT INTO GuildInfo (ChaNum, GuName) 
    VALUES (@ChaNum, @GuName)
    
    SELECT @error_var = @@ERROR
    IF @error_var <> 0 
    BEGIN
        -- ?? ??? ????
        SET @nReturn = -2
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    
    -----------------------------------------------------------------
    -- ??? ?? ????, ????? ????. 
    SELECT @nGuNum=@@IDENTITY
    
    SET @nReturn = @nGuNum
    
    -----------------------------------------------------------------
    -- ??? ??? ???(Guild Master)? ?????? ????? ????.
    UPDATE ChaInfo 
    SET GuNum=@nGuNum 
    WHERE ChaNum=@ChaNum
    
    -- ??? ????? ????.
    SET NOCOUNT OFF
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_guild]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_delete_guild]    
    @GuNum int,
    @ChaNum  int,	
	@nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int, -- ?? ??         
         @error_var int, 
		 @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    -----------------------------------------------------------------
    -- ????? ????.
    DELETE GuildInfo 
    WHERE GuNum=@GuNum AND ChaNum=@ChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
    -- ??? ???? ?? ????
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END    
    
    -----------------------------------------------------------------
    -- ??? ???? ?? ???? ????? 0 ?? ????.
    UPDATE ChaInfo 
    SET GuNum=0, GuPosition=0 
    WHERE GuNum=@GuNum
    
    -----------------------------------------------------------------
    -- ?? ???? ??? ????.
    DELETE GuildAlliance 
    WHERE GuNumP=@GuNum OR GuNumS=@GuNum
    
    SET @nReturn = 1
    
    -- ??? ????.
    SET NOCOUNT OFF
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_character]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_delete_character]
	@ChaNum  int,
	@nReturn int OUTPUT
AS    
    DECLARE
	@nGuNum int, -- ?? ??    
	@error_var int, 
	@rowcount_var int,
	@nChaDeleted int,
	@nExtreme int


	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	SET @nChaDeleted = 0
	SET @nExtreme = 0
	
	-----------------------------------------------------------------
	-- ?? ???? ?????? ????.
	SELECT @nChaDeleted=ChaDeleted FROM ChaInfo WHERE ChaNum=@ChaNum
	IF @nChaDeleted = 1
	BEGIN	
		SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	
	-----------------------------------------------------------------
    -- ?? ?? ???? ???? ??? ????.  
	SELECT @nGuNum=GuNum FROM GuildInfo WHERE ChaNum=@ChaNum
      
	IF @nGuNum <> 0 -- ??? ??, ??????? ??? ???? ??/?? ????? ???? ??.
	BEGIN 
		SET @nReturn = -2
		SET NOCOUNT OFF
		RETURN @nReturn
	END

	-----------------------------------------------------------------
	-- ??? ???? ????? ????.
	SELECT @nExtreme=ChaClass From ChaInfo Where ChaNum=@ChaNum
	
	-----------------------------------------------------------------
	-- ???? ????.
	UPDATE ChaInfo SET ChaDeleted=1 , ChaDeletedDate=getdate() WHERE ChaNum=@ChaNum
    
	IF @nExtreme=16
	BEGIN
		SET @nReturn = 1 -- ??? ??? ?????.
	END
	ELSE IF @nExtreme=32
	BEGIN
		SET @nReturn=2 -- ??? ??? ?????.
	END
	ELSE
	BEGIN
		SET @nReturn=0
	END
    
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_update_guild_rank]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_update_guild_rank]
    @nGuNum int,
    @nRank  int,	
	@nReturn int	OUTPUT
AS    
    DECLARE 
        @error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0	
    
    -- Set Guild Rank
    UPDATE GuildInfo 
    SET GuRank=@nRank 
    WHERE GuNum=@nGuNum
    
    -- Check Error
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1 -- ERROR
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0 -- SUCCESS
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  View [dbo].[viewGuildInfo]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
/*-----------------------------------------------------------------------------
 view_GuildInfo.sql
-----------------------------------------------------------------------------*/
CREATE VIEW [dbo].[viewGuildInfo]
AS
SELECT     dbo.GuildInfo.GuNum, dbo.GuildInfo.ChaNum, dbo.GuildInfo.GuDeputy, dbo.ChaInfo.ChaName, dbo.GuildInfo.GuName, dbo.GuildInfo.GuNotice, 
                      dbo.GuildInfo.GuRank, dbo.GuildInfo.GuMoney, dbo.GuildInfo.GuIncomeMoney, dbo.GuildInfo.GuMarkVer, dbo.GuildInfo.GuExpire, 
                      dbo.GuildInfo.GuMakeTime, dbo.GuildInfo.GuExpireTime, dbo.GuildInfo.GuAllianceSec, dbo.GuildInfo.GuAllianceDis, dbo.GuildInfo.GuAuthorityTime, 
                      dbo.GuildInfo.GuAllianceBattleLose, dbo.GuildInfo.GuAllianceBattleDraw, dbo.GuildInfo.GuAllianceBattleWin, dbo.GuildInfo.GuBattleLastTime, 
                      dbo.GuildInfo.GuBattleLose, dbo.GuildInfo.GuBattleDraw, dbo.GuildInfo.GuBattleWin, dbo.ChaInfo.ChaSpMID, dbo.ChaInfo.ChaSpSID
FROM         dbo.GuildInfo INNER JOIN
                      dbo.ChaInfo ON dbo.GuildInfo.ChaNum = dbo.ChaInfo.ChaNum
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "GuildInfo"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 114
               Right = 220
            End
            DisplayFlags = 280
            TopColumn = 20
         End
         Begin Table = "ChaInfo"
            Begin Extent = 
               Top = 6
               Left = 258
               Bottom = 114
               Right = 417
            End
            DisplayFlags = 280
            TopColumn = 68
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'viewGuildInfo'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'viewGuildInfo'
GO
/****** Object:  View [dbo].[viewGuildMember]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO
-------------------------------------------------------------------------------
-- view_GuildMember.sql
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewGuildMember]
AS
SELECT   dbo.GuildInfo.GuNum, dbo.ChaInfo.ChaNum, dbo.ChaInfo.ChaName, 
         dbo.ChaInfo.ChaGuName, dbo.ChaInfo.GuPosition
FROM     dbo.GuildInfo INNER JOIN
         dbo.ChaInfo ON dbo.GuildInfo.GuNum = dbo.ChaInfo.GuNum
WHERE   (dbo.GuildInfo.GuExpire = 0) AND (dbo.ChaInfo.ChaDeleted = 0)
GO
/****** Object:  StoredProcedure [dbo].[InsertGuildAlliance]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[InsertGuildAlliance]
	@nGuNump int,
	@nGuNumS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0

    INSERT INTO GuildAlliance (GuNumP, GuNumS) 
    VALUES (@nGuNump, @nGuNumS)
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[DeleteGuildAlliance]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[DeleteGuildAlliance]
	@nGuNumP int,
	@nGuNumS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	DELETE GuildAlliance 
	WHERE GuNumP=@nGuNumP AND GuNumS=@nGuNumS
	
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertVehicle]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return (nReturn)
-- DB_ERROR -1
-- DB_OK 0

-- Return (nVehicleNum)

CREATE PROCEDURE [dbo].[sp_InsertVehicle]
	@szVehicleName	  varchar(20),
	@nVehicleChaNum	  int,
	@nVehicleType	  int,	
	@nVehicleCardMID  int,
	@nVehicleCardSID  int,
	@nReturn		  int OUTPUT
As
	DECLARE
		@error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	SET @nReturn = 0

	BEGIN TRAN

	INSERT INTO VehicleInfo (VehicleName, VehicleChaNum, VehicleType, VehicleCardMID, VehicleCardSID, VehiclePutOnItems, VehicleColor)
	VALUES (@szVehicleName, @nVehicleChaNum, @nVehicleType, @nVehicleCardMID, @nVehicleCardSID, '', '')
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		UPDATE VehicleInfo SET VehicleNum=@@IDENTITY WHERE VehicleUniqueNum = @@IDENTITY
		SET @nReturn = @@IDENTITY
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_GetVehicleBattery]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- Battery amount
CREATE PROCEDURE [dbo].[sp_GetVehicleBattery]
	@nVehicleNum	int,
	@nVehicleChaNum	int,
	@nReturn	int OUTPUT
AS
	DECLARE
		@error_var int,
		@rowcount_var int,
		@VehicleBattery int
	
	SET NOCOUNT ON
	
	SET @nReturn = 0

	SELECT @VehicleBattery = VehicleBattery
	FROM VehicleInfo
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum=@nVehicleChaNum
	AND VehicleDeleted=0	
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = @VehicleBattery
	END
	
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_DeleteVehicle]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_DeleteVehicle]
	@nVehicleNum	int,
	@nVehicleChaNum int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE VehicleInfo
	SET VehicleDeleted=1, VehicleDeletedDate=getdate()
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum=@nVehicleChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_SelectVehicle]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_SelectVehicle]
	@nVehicleNum		int,
	@nVehicleChaNum		int
AS
	SET NOCOUNT ON
	
	SELECT VehicleChaNum, VehicleCardMID, VehicleCardSID,
	VehicleType, VehicleBattery, VehicleBooster FROM VehicleInfo WHERE VehicleNum = @nVehicleNum And VehicleChaNum = @nVehicleChaNum

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdateVehicleBooster]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdateVehicleBooster]
	@nVehicleNum	 int,
	@nVehicleChaNum	 int,
	@nVehicleBooster int,
	@nReturn		int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE VehicleInfo
	SET VehicleBooster=@nVehicleBooster
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum = @nVehicleChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdateVehicleBattery]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdateVehicleBattery]
	@nVehicleNum	 int,
	@nVehicleChaNum	 int,
	@nVehicleBattery int,
	@nReturn		int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE VehicleInfo
	SET VehicleBattery=@nVehicleBattery
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum = @nVehicleChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[MakeUserInven]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[MakeUserInven]
    @nSGNum int,
    @nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	INSERT INTO UserInven (SGNum, UserNum, UserMoney, UserInven) 
	VALUES(@nSGNum, @nUserNum, 0,'')	
	
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[UpdateUserMoney]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateUserMoney]    
    @nUserNum int,
    @llMoney money
AS		
	SET NOCOUNT ON
	
	UPDATE UserInven
	SET UserMoney=@llMoney
	WHERE UserNum=@nUserNum

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[GetInvenCount]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetInvenCount]    
    @nUserNum int,
	@nReturn int OUTPUT
AS		
	SET NOCOUNT ON
	
	SET @nReturn = 0		

	IF EXISTS (SELECT UserInvenNum FROM UserInven WHERE UserNum=@nUserNum) 
	BEGIN
		SET @nReturn = 1
	END
	ELSE
	BEGIN
        SET @nReturn = 0
	END
	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_SelectPet]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_SelectPet]
	@nPetNum		int,
	@nReturn		int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	SELECT PetNum, PetName, PetChaNum, PetType, PetMID, PetSID, PetStyle, PetColor, PetFull, PetDeleted, PetCreateDate, PetDeletedDate
	FROM PetInfo
	WHERE PetNum=@nPetNum And PetDeleted=0

	SELECT @error_var = @@ERROR

	IF @error_var <> 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = 0
	END    

	SELECT PetInvenNum, PetNum, PetInvenType, PetInvenMID, PetInvenSID, PetInvenCMID, PetInvenCSID, PetInvenAvailable, PetInvenUpdateDate
	FROM PetInven
	Where PetNum=@nPetNum
	Order By PetInvenType, PetInvenMID, PetInvenSID

	SELECT @error_var = @error_var+@@ERROR, @rowcount_var = @@ROWCOUNT

	IF @error_var <> 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = 0
	END    


	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetInven]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetInven]
	@nChaNum			int,
	@nPetNum		    int,
	@nPetInvenType		int,
	@nPetInvenMID		int,
	@nPetInvenSID		int,
	@nPetInvenCMID		int,
	@nPetInvenCSID		int,
	@nPetInvenAvailable	int,
	@nReturn		int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	-- @nPetInvenType = 1 : Accessory for A type
	-- @nPetInvenType = 2 : Accessory for B type
	-- @nPetInvenType = 3 : Skll

	If @nPetInvenType=1 OR @nPetInvenType=2
	BEGIN
		UPDATE PetInven
		SET PetInvenMID = @nPetInvenMID
		, PetInvenSID = @nPetInvenSID
		, PetInvenCMID = @nPetInvenCMID
		, PetInvenCSID = @nPetInvenCSID
		, PetInvenUpdateDate = getdate()		
		WHERE PetNum = @nPetNum And PetChaNum=@nChaNum
		And PetInvenType = @nPetInvenType
	END
	Else If @nPetInvenType=3
	BEGIN
		UPDATE PetInven
		SET PetInvenCMID = @nPetInvenCMID
		, PetInvenCSID = @nPetInvenCSID
		, PetInvenAvailable = @nPetInvenAvailable
		, PetInvenUpdateDate = getdate()		
		WHERE PetNum = @nPetNum
		And PetChaNum = @nChaNum
		And PetInvenType = @nPetInvenType
		And PetInvenMID = @nPetInvenMID
		And PetInvenSID = @nPetInvenSID
	END

	-- PetInven Update Return Result
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    

	IF @error_var <> 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	IF (@error_var=0 AND @rowcount_var=0)
	BEGIN
		BEGIN TRAN		

		INSERT INTO PetInven (PetNum, PetChaNum, PetInvenType, PetInvenMID, PetInvenSID, PetInvenCMID, PetInvenCSID, PetInvenAvailable)
		Values (@nPetNum, @nChaNum, @nPetInvenType, @nPetInvenMID, @nPetInvenSID, @nPetInvenCMID, @nPetInvenCSID, @nPetInvenAvailable)

		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	
		IF @error_var <> 0 OR @rowcount_var = 0
		BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
		END
		ELSE
		BEGIN
			COMMIT TRAN
			SET @nReturn = 0
		END    
	END
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetFull]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetFull]
	@nChaNum	int,
	@nPetNum	int,
	@nPetFull	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetFull=@nPetFull
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetDualSkill]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetDualSkill]
	@nChaNum	int,
	@nPetNum	int,
	@nPetDualSkill	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetDualSkill=@nPetDualSkill
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetColor]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetColor]
	@nChaNum	int,
	@nPetNum	int,
	@nPetColor	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetColor=@nPetColor
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetChaNum]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetChaNum]
	@nPetChaNum	int,
	@nPetNum	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetChaNum=@nPetChaNum
	WHERE PetNum=@nPetNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_RestorePet]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return (nReturn)
-- DB_ERROR -1
-- DB_OK 0

-- Return (nPetNum)

CREATE PROCEDURE [dbo].[sp_RestorePet]
	@nPetNum	int,
	@nPetChaNum	int,
	@nReturn	int OUTPUT
As
	DECLARE
		@error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	SET @nReturn = 0

	BEGIN TRAN

	Update PetInfo Set PetDeleted=0, PetFull=1000, PetPutOnItems=''
	Where PetNum=@nPetNum And PetChaNum=@nPetChaNum And PetDeleted=1
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = @nPetNum
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_RenamePet]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_RenamePet]
	@nChaNum	int,
	@nPetNum	int,
	@szPetName	varchar(20),
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nPetNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nPetNumTemp = 0
	
	SELECT @nPetNumTemp=PetNum FROM PetInfo WHERE PetName=@szPetName
	
	IF @nPetNumTemp <> 0 -- Exist PET Name
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		BEGIN TRAN

		UPDATE PetInfo
		SET PetName=@szPetName
		WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
		IF @error_var <> 0 OR @rowcount_var = 0
		BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
		END
		ELSE
		BEGIN
			COMMIT TRAN
			SET @nReturn = 0
		END    
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetStyle]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetStyle]
	@nChaNum	int,
	@nPetNum	int,
	@nPetStyle	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetStyle=@nPetStyle
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_DeletePet]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_DeletePet]
	@nChaNum	int,
	@nPetNum	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetDeleted=1, PetDeletedDate=getdate()
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_GetPetFull]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- Full amount
create PROCEDURE [dbo].[sp_GetPetFull]
	@nChaNum	int,
	@nPetNum	int,	
	@nReturn	int OUTPUT
AS
	DECLARE
		@error_var int,
		@rowcount_var int,
		@PetFull int
	
	SET NOCOUNT ON
	
	SET @nReturn = 0

	SELECT @PetFull = PetFull
	FROM PetInfo
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum And PetDeleted=0	
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = @PetFull
	END
	
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertPet]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_InsertPet]
	@szPetName	  varchar(20),
	@nPetChaNum	  int,
	@nPetType	  int,
	@nPetMID	  int,
	@nPetSID	  int,
	@nPetCardMID       int,
	@nPetCardSID  	  int,
	@nPetStyle	  int,
	@nPetColor	  int,
	@nReturn	  int OUTPUT
As
	DECLARE
		@error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	SET @nReturn = 0

	BEGIN TRAN

	Insert Into PetInfo (PetName, PetChaNum, PetType, PetMID, PetSID, PetCardMID, PetCardSID, PetStyle, PetColor, PetPutOnItems)
	Values (@szPetName, @nPetChaNum, @nPetType, @nPetMID, @nPetSID, @nPetCardMID, @nPetCardSID, @nPetStyle, @nPetColor, '')
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		UPDATE PetInfo SET PetNum = @@IDENTITY WHERE PetUniqueNum = @@IDENTITY
		SET @nReturn = @@IDENTITY
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[InsertPartyMatch]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[InsertPartyMatch]
	@nSGNum  int,
	@nSvrNum int,
    @nWin    int,
	@nLost   int
AS
	SET NOCOUNT ON

	INSERT INTO LogPartyMatch (SGNum, SvrNum, Win, Lost) 
	VALUES (@nSGNum, @nSvrNum, @nWin, @nLost)

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_Extreme]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- ??? ?/? ?? ??? ????.
CREATE   PROCEDURE [dbo].[sp_Extreme]
	@nUserNum	int

AS	
	DECLARE
		@error_var int, 
		@rowcount_var int	

	SET NOCOUNT ON
Select (MSum-MS) As M, (FSum-FS) As F
From
(
	Select isnull(Sum(M),0) As MSum, isnull(Sum(F),0) As FSum, isnull(Sum(MS),0) As MS, isnull(Sum(FS),0) As FS
	From
	(
	Select ChaClass
	,
	Case ChaClass
	When 1 Then 1
	When 2 Then 1
	When 256 Then 1
	When 512 Then 1
	Else 0
	End As M
	,
	Case ChaClass
	When 4 Then 1
	When 8 Then 1
	When 64 Then 1
	When 128 Then 1
	Else 0
	End As F
	,
	Case ChaClass
	When 16 Then 
		Case ChaDeleted
		When 4 Then 0
		Else 1
		End
	Else 0
	End As MS
	,
	Case ChaClass
	When 32 Then 
		Case ChaDeleted
		When 4 Then 0
		Else 1
		End
	Else 0
	End As FS
	From ChaInfo
	) As t
) As tt
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_guild_member]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_delete_guild_member]
    @ChaNum int,
    @nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int,
         @error_var int, 
         @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    UPDATE ChaInfo 
    SET GuNum=0, GuPosition=0, ChaGuSecede=getdate()
    WHERE ChaNum=@ChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN    
        SET @nReturn = 1        
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_add_guild_member]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_add_guild_member]
    @GuNum int,
    @ChaNum int,
	@nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int, -- ?? ??         
         @error_var int, 
		 @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    -----------------------------------------------------------------
    -- Character ? ?? ????? ?????.
    UPDATE ChaInfo 
    SET GuNum=@GuNum 
    WHERE ChaNum=@ChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
    -- ??? ???? ?? ????
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN    
        SET @nReturn = 1
        -- ??? ????.
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[RenameCharacter]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[RenameCharacter]
	@nChaNum int,
	@szChaName varchar(33),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0
	
	SELECT @nChaNumTemp=ChaNum FROM ChaInfo WHERE ChaName=@szChaName
	
	IF @nChaNumTemp <> 0 -- ???? ?? ??
	BEGIN
		SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END
	
    UPDATE ChaInfo
    SET ChaName=@szChaName
    WHERE ChaNum=@nChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaFaceStyle]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaFaceStyle]
	@nChaNum int,
	@nChaFaceStyle int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0	
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaFace=@nChaFaceStyle
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaExp]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaExp]
	@llExp money,
	@nChaNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0

    UPDATE ChaInfo WITH (UPDLOCK) 
    SET ChaExp=@llExp
    WHERE ChaNum=@nChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[UpdateAllCharacterOffline]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateAllCharacterOffline]
AS
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	UPDATE ChaInfo WITH (UPDLOCK) 
	SET ChaOnline=0
	WHERE ChaOnline=1
	
    SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdateChaGender]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_UpdateChaGender]
	@nChaNum int,
	@nChaClass int,
	@nChaSex int,
	@nFace int,
	@nChaHair int,
	@nChaHairColor int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn=0
	SET @nChaNumTemp=0
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaClass=@nChaClass, ChaSex=@nChaSex, ChaFace=@nFace, ChaHair=@nChaHair, ChaHairColor=@nChaHairColor
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaOnline]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaOnline]
	@nChaNum int,
	@nChaOnline int
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	UPDATE ChaInfo
	SET ChaOnline=@nChaOnline 
	WHERE ChaNum=@nChaNum
	
    SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaLastCallPos]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaLastCallPos]
	@nChaReturnMap int,
	@fChaReturnPosX float,
	@fChaReturnPosY float,
	@fChaReturnPosZ float,
	@nChaNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0

    UPDATE ChaInfo SET
    ChaReturnMap=@nChaReturnMap,
    ChaReturnPosX=@fChaReturnPosX,
    ChaReturnPosY=@fChaReturnPosY,
    ChaReturnPosZ=@fChaReturnPosZ
    WHERE ChaNum=@nChaNum    
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaHairStyle]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaHairStyle]
	@nChaNum int,
	@nChaHairStyle int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0	
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaHair=@nChaHairStyle
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaHairColor]    Script Date: 10/25/2015 16:51:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaHairColor]
	@nChaNum int,
	@nChaHairColor int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0	
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaHairColor=@nChaHairColor
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END
GO
