USE [RanLog]
GO
/****** Object:  Table [dbo].[LogAction]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogAction](
	[ActionNum] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [int] NOT NULL CONSTRAINT [DF_LogAction_ChaNum]  DEFAULT ((0)),
	[Type] [int] NOT NULL CONSTRAINT [DF_LogAction_Type]  DEFAULT ((0)),
	[TargetNum] [int] NOT NULL CONSTRAINT [DF_LogAction_TargetNum]  DEFAULT ((0)),
	[TargetType] [int] NOT NULL CONSTRAINT [DF_LogAction_TargetType]  DEFAULT ((0)),
	[BrightPoint] [int] NOT NULL CONSTRAINT [DF_LogAction_BrightPoint]  DEFAULT ((0)),
	[LifePoint] [int] NOT NULL CONSTRAINT [DF_LogAction_LifePoint]  DEFAULT ((0)),
	[ExpPoint] [money] NOT NULL CONSTRAINT [DF_LogAction_ExpPoint]  DEFAULT ((0)),
	[ActionMoney] [money] NOT NULL CONSTRAINT [DF_LogAction_ActionMoney]  DEFAULT ((0)),
	[ActionDate] [datetime] NOT NULL CONSTRAINT [DF_LogAction_ActionDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_LogAction] PRIMARY KEY CLUSTERED 
(
	[ActionNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogVehicleActionFlag]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogVehicleActionFlag](
	[VehicleActionFlag] [int] NOT NULL,
	[VehicleActionName] [varchar](50) NOT NULL,
 CONSTRAINT [PK_LogVehicleActinoFlag] PRIMARY KEY CLUSTERED 
(
	[VehicleActionFlag] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogVehicleAction]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogVehicleAction](
	[ActionNum] [bigint] IDENTITY(1,1) NOT NULL,
	[VehicleNum] [int] NOT NULL CONSTRAINT [DF_LogVehicleAction_VehicleNum]  DEFAULT ((0)),
	[ItemMID] [smallint] NOT NULL CONSTRAINT [DF_LogVehicleAction_ItemMID]  DEFAULT ((0)),
	[ItemSID] [smallint] NOT NULL CONSTRAINT [DF_LogVehicleAction_ItemSID]  DEFAULT ((0)),
	[ActionType] [smallint] NOT NULL CONSTRAINT [DF_LogVehicleAction_ActionType]  DEFAULT ((0)),
	[VehicleBattery] [int] NOT NULL CONSTRAINT [DF_LogVehicleAction_VehicleBattery]  DEFAULT ((0)),
	[LogDate] [datetime] NOT NULL CONSTRAINT [DF_LogVehicleAction_LogDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_LogVehicleAction] PRIMARY KEY CLUSTERED 
(
	[ActionNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogServerState]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogServerState](
	[SvrStateNum] [int] IDENTITY(1,1) NOT NULL,
	[LogDate] [datetime] NOT NULL CONSTRAINT [DF_LogServer_LogDate]  DEFAULT (getdate()),
	[UserNum] [int] NOT NULL CONSTRAINT [DF_LogServer_UserNum]  DEFAULT ((0)),
	[UserMaxNum] [int] NOT NULL CONSTRAINT [DF_LogServer_UserMaxNum]  DEFAULT ((0)),
	[SvrNum] [int] NOT NULL CONSTRAINT [DF_LogServer_SvrNum]  DEFAULT ((0)),
	[SGNum] [int] NOT NULL CONSTRAINT [DF_LogServer_SGNum]  DEFAULT ((0)),
 CONSTRAINT [PK_LogServerState] PRIMARY KEY CLUSTERED 
(
	[SvrStateNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogPetActionFlag]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogPetActionFlag](
	[PetActionFlag] [int] NOT NULL,
	[PetActionName] [varchar](50) NOT NULL,
 CONSTRAINT [PK_LogPetActinoFlag] PRIMARY KEY CLUSTERED 
(
	[PetActionFlag] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogPetAction]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogPetAction](
	[ActionNum] [bigint] IDENTITY(1,1) NOT NULL,
	[PetNum] [int] NOT NULL CONSTRAINT [DF_LogPetAction_PetNum]  DEFAULT ((0)),
	[ItemMID] [smallint] NOT NULL CONSTRAINT [DF_LogPetAction_ItemMID]  DEFAULT ((0)),
	[ItemSID] [smallint] NOT NULL CONSTRAINT [DF_LogPetAction_ItemSID]  DEFAULT ((0)),
	[ActionType] [smallint] NOT NULL CONSTRAINT [DF_LogPetAction_ActionType]  DEFAULT ((0)),
	[PetFull] [int] NOT NULL CONSTRAINT [DF_LogPetAction_PetFull]  DEFAULT ((0)),
	[LogDate] [datetime] NOT NULL CONSTRAINT [DF_LogPetAction_LogDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_LogPetAction] PRIMARY KEY CLUSTERED 
(
	[ActionNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogMakeType]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogMakeType](
	[MakeType] [int] NOT NULL,
	[MakeName] [varchar](20) NULL,
 CONSTRAINT [PK_LogMakeType] PRIMARY KEY CLUSTERED 
(
	[MakeType] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogItemRandom]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogItemRandom](
	[RandomNum] [bigint] IDENTITY(1,1) NOT NULL,
	[NIDMain] [smallint] NULL CONSTRAINT [DF_LogItemRandom_NIDMain]  DEFAULT ((0)),
	[NIDSub] [smallint] NULL CONSTRAINT [DF_LogItemRandom_NIDSub]  DEFAULT ((0)),
	[SGNum] [tinyint] NULL CONSTRAINT [DF_LogItemRandom_SGNum]  DEFAULT ((0)),
	[SvrNum] [tinyint] NULL CONSTRAINT [DF_LogItemRandom_SvrNum]  DEFAULT ((0)),
	[FldNum] [tinyint] NULL CONSTRAINT [DF_LogItemRandom_FldNum]  DEFAULT ((0)),
	[MakeType] [tinyint] NOT NULL CONSTRAINT [DF_LogItemRandom_MakeType]  DEFAULT ((0)),
	[MakeNum] [money] NOT NULL CONSTRAINT [DF_LogItemRandom_MakeNum]  DEFAULT ((0)),
	[RandomType1] [tinyint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomType1]  DEFAULT ((0)),
	[RandomValue1] [smallint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomValue1]  DEFAULT ((0)),
	[RandomType2] [tinyint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomType2]  DEFAULT ((0)),
	[RandomValue2] [smallint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomValue2]  DEFAULT ((0)),
	[RandomType3] [tinyint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomType3]  DEFAULT ((0)),
	[RandomValue3] [smallint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomValue3]  DEFAULT ((0)),
	[RandomType4] [tinyint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomType4]  DEFAULT ((0)),
	[RandomValue4] [smallint] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomValue4]  DEFAULT ((0)),
	[RandomDate] [smalldatetime] NOT NULL CONSTRAINT [DF_LogItemRandom_RandomDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_LogItemRandom] PRIMARY KEY CLUSTERED 
(
	[RandomNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogItemMax]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogItemMax](
	[NIDMain] [int] NOT NULL CONSTRAINT [DF_LogItemMax_NIDMain]  DEFAULT ((0)),
	[NIDSub] [int] NOT NULL CONSTRAINT [DF_LogItemMax_NIDSub]  DEFAULT ((0)),
	[SGNum] [int] NOT NULL CONSTRAINT [DF_LogItemMax_SGNum]  DEFAULT ((0)),
	[SvrNum] [int] NOT NULL CONSTRAINT [DF_LogItemMax_SvrNum]  DEFAULT ((0)),
	[FldNum] [int] NOT NULL CONSTRAINT [DF_LogItemMax_FldNum]  DEFAULT ((0)),
	[MakeType] [int] NOT NULL CONSTRAINT [DF_LogItemMax_MakeType]  DEFAULT ((0)),
	[MaxNum] [money] NULL CONSTRAINT [DF_LogItemMax_MaxNum]  DEFAULT ((0)),
 CONSTRAINT [PK_LogItemMax] PRIMARY KEY CLUSTERED 
(
	[NIDMain] ASC,
	[NIDSub] ASC,
	[SGNum] ASC,
	[SvrNum] ASC,
	[FldNum] ASC,
	[MakeType] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogItemExchange]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogItemExchange](
	[ExchangeNum] [bigint] IDENTITY(1,1) NOT NULL,
	[NIDMain] [int] NULL CONSTRAINT [DF_LogItemExchange_NIDMain_200511]  DEFAULT ((0)),
	[NIDSub] [int] NULL CONSTRAINT [DF_LogItemExchange_NIDSub_200511]  DEFAULT ((0)),
	[SGNum] [int] NULL CONSTRAINT [DF_LogItemExchange_SGNum_200511]  DEFAULT ((0)),
	[SvrNum] [int] NULL CONSTRAINT [DF_LogItemExchange_SvrNum_200511]  DEFAULT ((0)),
	[FldNum] [int] NULL CONSTRAINT [DF_LogItemExchange_FldNum_200511]  DEFAULT ((0)),
	[MakeType] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_MakeType_200511]  DEFAULT ((0)),
	[MakeNum] [money] NOT NULL CONSTRAINT [DF_LogItemExchange_MakeNum_200511]  DEFAULT ((0)),
	[ItemAmount] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_ItemAmount_200511]  DEFAULT ((0)),
	[ItemFromFlag] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_ItemFromFlag_200511]  DEFAULT ((0)),
	[ItemFrom] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_ItemFrom_200511]  DEFAULT ((0)),
	[ItemToFlag] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_ItemToFlag_200511]  DEFAULT ((0)),
	[ItemTo] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_ItemTo_200511]  DEFAULT ((0)),
	[ExchangeFlag] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_ExchangeFlag_200511]  DEFAULT ((0)),
	[ExchangeDate] [datetime] NOT NULL CONSTRAINT [DF_LogItemExchange_ExchangeDate_200511]  DEFAULT (getdate()),
	[Damage] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_Damage_200511]  DEFAULT ((0)),
	[Defense] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_Defense_200511]  DEFAULT ((0)),
	[Fire] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_Fire_200511]  DEFAULT ((0)),
	[Ice] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_Ice_200511]  DEFAULT ((0)),
	[Poison] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_Poison_200511]  DEFAULT ((0)),
	[Electric] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_Electric_200511]  DEFAULT ((0)),
	[Spirit] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_Spirit_200511]  DEFAULT ((0)),
	[CostumeMID] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_CostumeMID_200511]  DEFAULT ((0)),
	[CostumeSID] [int] NOT NULL CONSTRAINT [DF_LogItemExchange_CostumeSID_200511]  DEFAULT ((0)),
	[TradePrice] [money] NOT NULL CONSTRAINT [DF_LogItemExchange_TradePrice_200511]  DEFAULT ((0)),
 CONSTRAINT [PK_LogItemExchange_200511] PRIMARY KEY NONCLUSTERED 
(
	[ExchangeNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[HackProgramList]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[HackProgramList](
	[HackProgramNum] [int] NOT NULL,
	[HackProgramName] [varchar](100) NOT NULL CONSTRAINT [DF_HackProgramList_HackProgramName]  DEFAULT (''),
 CONSTRAINT [PK_HackProgramList] PRIMARY KEY CLUSTERED 
(
	[HackProgramNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogHackProgram]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogHackProgram](
	[HackNum] [int] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL CONSTRAINT [DF_LogHackProgram_UserNum]  DEFAULT ((0)),
	[ChaNum] [int] NOT NULL CONSTRAINT [DF_LogHackProgram_ChaNum]  DEFAULT ((0)),
	[SGNum] [int] NOT NULL CONSTRAINT [DF_LogHackProgram_SvrGrp]  DEFAULT ((0)),
	[SvrNum] [int] NOT NULL CONSTRAINT [DF_LogHackProgram_SvrNum]  DEFAULT ((0)),
	[HackProgramNum] [int] NOT NULL CONSTRAINT [DF_LogHackProgram_HackProgramNum]  DEFAULT ((0)),
	[HackDate] [datetime] NOT NULL CONSTRAINT [DF_LogHackProgram_HackDate]  DEFAULT (getdate()),
	[HackComment] [varchar](512) NOT NULL CONSTRAINT [DF__LogHackPr__HackC__6D0D32F4]  DEFAULT (''),
 CONSTRAINT [PK_LogHackProgram] PRIMARY KEY CLUSTERED 
(
	[HackNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogExchangeFlag]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogExchangeFlag](
	[ExchangeFlag] [int] NOT NULL,
	[ExchangeName] [varchar](50) NULL,
 CONSTRAINT [PK_LogExchangeFlag] PRIMARY KEY CLUSTERED 
(
	[ExchangeFlag] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_LogAction_Insert]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_LogAction_Insert]
	@nChaNum int,
	@nType int,
    @nTargetNum int,
    @nTargetType int,
    @nExpPoint money,
    @nBrightPoint int,
    @nLifePoint int,
    @nMoney money
AS	
	SET NOCOUNT ON

	INSERT INTO LogAction (ChaNum,   Type,   TargetNum,   TargetType,   ExpPoint,   BrightPoint,   LifePoint,   ActionMoney) 
    VALUES    (@nChaNum, @nType, @nTargetNum, @nTargetType, @nExpPoint, @nBrightPoint, @nLifePoint, @nMoney)

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_LogVehicleAction_Insert]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0

CREATE Procedure [dbo].[sp_LogVehicleAction_Insert]
	@VehicleNum int,
	@ItemMID int,
	@ItemSID int,
	@ActionType int,	
	@VehicleBattery int,
	@nReturn int OUTPUT
AS
	DECLARE
	@error_var int,
	@rowcount_var int
	SET NOCOUNT ON

	SET @nReturn=0

	BEGIN TRAN

	Insert Into LogVehicleAction( VehicleNum, ItemMID, ItemSID, ActionType, VehicleBattery )
	Values( @VehicleNum, @ItemMID, @ItemSID, @ActionType, @VehicleBattery )

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var<>0 OR @rowcount_var=0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn=-1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn=0
	END

	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[log_serverstate]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
Create Procedure [dbo].[log_serverstate]	
	@usernum int,
	@usermax int,
    @svrnum   int,
	@sgnum    int
AS
	SET NOCOUNT ON

	INSERT INTO LogServerState (UserNum, UserMaxNum, SvrNum, SGNum) 
	VALUES (@usernum, @usermax, @svrnum, @sgnum)

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_LogPetAction_Insert]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0

CREATE Procedure [dbo].[sp_LogPetAction_Insert]
	@PetNum int,
	@ItemMID int,
	@ItemSID int,
	@ActionType int,	
	@PetFull int,
	@nReturn int OUTPUT
AS
	DECLARE
	@error_var int,
	@rowcount_var int
	SET NOCOUNT ON

	SET @nReturn=0

	BEGIN TRAN

	Insert Into LogPetAction( PetNum, ItemMID, ItemSID, ActionType, PetFull )
	Values( @PetNum, @ItemMID, @ItemSID, @ActionType, @PetFull )

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var<>0 OR @rowcount_var=0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn=-1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn=0
	END

	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_LogItemRandom_Insert]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0

CREATE Procedure [dbo].[sp_LogItemRandom_Insert]
	@NIDMain int,
	@NIDSub int,
	@SGNum int,
	@SvrNum int,
	@FldNum int,
	@MakeType int,
	@MakeNum money,
	@RandomType1 int, 
	@RandomValue1 int, 
	@RandomType2 int, 
	@RandomValue2 int, 
	@RandomType3 int, 
	@RandomValue3 int, 
	@RandomType4 int, 
	@RandomValue4 int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int
	SET NOCOUNT ON

	SET @nReturn = 0

	BEGIN TRAN

	Insert Into LogItemRandom (
		NIDMain, NIDSub, SGNum, SvrNum, FldNum, MakeType, MakeNum
		, RandomType1, RandomValue1, RandomType2, RandomValue2
		, RandomType3, RandomValue3, RandomType4, RandomValue4)
	Values (
		@NIDMain, @NIDSub, @SGNum, @SvrNum, @FldNum, @MakeType, @MakeNum
		, @RandomType1, @RandomValue1, @RandomType2, @RandomValue2
		, @RandomType3, @RandomValue3, @RandomType4, @RandomValue4
	)

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
/****** Object:  View [dbo].[viewLogItemExchangeMax]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO
-------------------------------------------------------------------------------
-- viewLogItemExchangeMax
CREATE VIEW [dbo].[viewLogItemExchangeMax]
AS
SELECT   TOP 100 PERCENT MAX(MakeNum) AS MaxNum, NIDMain, NIDSub, MakeType, 
                SGNum, SvrNum, FldNum
FROM      dbo.LogItemExchange
GROUP BY SGNum, SvrNum, FldNum, MakeType, NIDMain, NIDSub
ORDER BY SGNum, SvrNum, FldNum, MakeType, NIDMain, NIDSub, MaxNum
GO
/****** Object:  StoredProcedure [dbo].[sp_logitemexchange_insert]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE Procedure [dbo].[sp_logitemexchange_insert]
    @NIDMain int,
	@NIDSub int,
	@SGNum int,
	@SvrNum int,
	@FldNum int,
	
	@MakeType int,
	@MakeNum money,
	@ItemAmount int,
	@ItemFromFlag int,
	@ItemFrom int,
	
	@ItemToFlag int,
	@ItemTo int,
	@ExchangeFlag int,
	@Damage int,
	@Defense int,
	
	@Fire int,
	@Ice int,
	@Poison int,
	@Electric int,
	@Spirit int,
	
	@CostumeMID int,
	@CostumeSID int,
	@TradePrice money,    
	@nReturn int OUTPUT
AS
	DECLARE 	
		@error_var int -- Declare variables used in error checking.

	SET NOCOUNT ON

	INSERT INTO LogItemExchange (NIDMain, NIDSub, SGNum, SvrNum, FldNum,
	MakeType, MakeNum, ItemAmount, ItemFromFlag, ItemFrom, 
	ItemToFlag, ItemTo, ExchangeFlag, Damage, Defense,
	Fire, Ice, Poison, Electric, Spirit,
	CostumeMID, CostumeSID, TradePrice) VALUES 
	(@NIDMain, @NIDSub, @SGNum, @SvrNum, @FldNum,
	@MakeType, @MakeNum, @ItemAmount, @ItemFromFlag, @ItemFrom,
	@ItemToFlag, @ItemTo, @ExchangeFlag, @Damage, @Defense,
	@Fire, @Ice, @Poison, @Electric, @Spirit,
	@CostumeMID, @CostumeSID, @TradePrice)

	SELECT @error_var = @@ERROR
	IF @error_var <> 0 
	BEGIN
	    -- 火涝角菩
	    SET @nReturn = 0	    
	END
        ELSE
        BEGIN
	    -- 沥惑利栏肺 火涝 己傍
	    SET @nReturn = 1
        END

	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  View [dbo].[viewLogHackProgram]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[viewLogHackProgram]
AS
SELECT   TOP 100 PERCENT dbo.LogHackProgram.HackNum, 
                dbo.LogHackProgram.UserNum, dbo.LogHackProgram.ChaNum, 
                dbo.LogHackProgram.SGNum, dbo.LogHackProgram.SvrNum, 
                dbo.LogHackProgram.HackProgramNum, dbo.LogHackProgram.HackDate, 
                dbo.LogHackProgram.HackComment, 
                dbo.HackProgramList.HackProgramName
FROM      dbo.LogHackProgram LEFT OUTER JOIN
                dbo.HackProgramList ON 
                dbo.LogHackProgram.HackProgramNum = dbo.HackProgramList.HackProgramNum
GO
/****** Object:  StoredProcedure [dbo].[InsertLogHackProgram]    Script Date: 10/25/2015 16:52:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[InsertLogHackProgram]
	@nSGNum int,
	@nSvrNum int,
	@nUserNum int,
	@nChaNum int,
	@nHackProgramNum int,
	@strComment varchar (512),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0

    INSERT INTO LogHackProgram (SGNum,   SvrNum,   UserNum,   ChaNum,   HackProgramNum,   HackComment) 
    VALUES (@nSGNum, @nSvrNum, @nUserNum, @nChaNum, @nHackProgramNum, @strComment)
    
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
