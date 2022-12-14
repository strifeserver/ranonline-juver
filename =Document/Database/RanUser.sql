USE [RanUser]
GO
/****** Object:  Table [dbo].[ServerGroup]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ServerGroup](
	[SGNum] [int] NOT NULL,
	[SGName] [varchar](50) NOT NULL CONSTRAINT [DF_ServerGroup_SGName]  DEFAULT (''),
	[OdbcName] [varchar](50) NOT NULL CONSTRAINT [DF_ServerGroup_OdbcName]  DEFAULT (''),
	[OdbcUserID] [varchar](20) NOT NULL CONSTRAINT [DF_ServerGroup_OdbcUserID]  DEFAULT (''),
	[OdbcPassword] [varchar](20) NOT NULL CONSTRAINT [DF_ServerGroup_OdbcPassword]  DEFAULT (''),
	[OdbcLogName] [varchar](50) NOT NULL CONSTRAINT [DF_ServerGroup_OdbcLogName]  DEFAULT (''),
	[OdbcLogUserID] [varchar](20) NOT NULL CONSTRAINT [DF_ServerGroup_OdbcLogUserID]  DEFAULT (''),
	[OdbcLogPassword] [varchar](20) NOT NULL CONSTRAINT [DF_ServerGroup_OdbcLogPassword]  DEFAULT (''),
PRIMARY KEY CLUSTERED 
(
	[SGNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[newcheckid]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[newcheckid](
	[Id] [varchar](18) NOT NULL,
	[CreateDate] [datetime] NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogServerState]    Script Date: 10/25/2015 16:52:54 ******/
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
/****** Object:  Table [dbo].[LogLogin]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogLogin](
	[LoginNum] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[LogInOut] [int] NOT NULL CONSTRAINT [DF_LogLogin_LogInOut]  DEFAULT ((0)),
	[LogDate] [datetime] NULL CONSTRAINT [DF_LogLogin_LogDate]  DEFAULT (getdate()),
	[LogIpAddress] [varchar](23) NULL,
 CONSTRAINT [PK_LogLogin] PRIMARY KEY CLUSTERED 
(
	[LoginNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogGmCmd]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogGmCmd](
	[GmCmdNum] [int] IDENTITY(1,1) NOT NULL,
	[LogDate] [datetime] NULL CONSTRAINT [DF_LogGmCmd_LogDate]  DEFAULT (getdate()),
	[GmCmd] [varchar](200) NULL,
	[UserNum] [int] NULL,
 CONSTRAINT [PK_LogGmCmd] PRIMARY KEY CLUSTERED 
(
	[GmCmdNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LogGameTime]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LogGameTime](
	[GameTimeNum] [bigint] IDENTITY(1,1) NOT NULL,
	[LogDate] [datetime] NOT NULL CONSTRAINT [DF_LogGameTime_LogDate]  DEFAULT (getdate()),
	[GameTime] [int] NOT NULL CONSTRAINT [DF_LogGameTime_GameTime]  DEFAULT ((0)),
	[UserID] [varchar](20) NULL,
	[UserNum] [int] NULL CONSTRAINT [DF_LogGameTime_UserNum]  DEFAULT ((0)),
	[SGNum] [int] NULL CONSTRAINT [DF_LogGameTime_SGNum]  DEFAULT ((0)),
	[SvrNum] [int] NULL CONSTRAINT [DF_LogGameTime_SvrNum]  DEFAULT ((0)),
	[ChaNum] [int] NULL CONSTRAINT [DF_LogGameTime_ChaNum]  DEFAULT ((0)),
 CONSTRAINT [PK_LogGameTime] PRIMARY KEY CLUSTERED 
(
	[GameTimeNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UserInfo]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserInfo](
	[UserNum] [int] IDENTITY(1,1) NOT NULL,
	[UserName] [varchar](20) NOT NULL CONSTRAINT [DF_UserInfo_UserName]  DEFAULT (''),
	[UserID] [varchar](20) NOT NULL CONSTRAINT [DF_UserInfo_UserID]  DEFAULT (''),
	[UserPass] [varchar](20) NOT NULL CONSTRAINT [DF_UserInfo_UserPass]  DEFAULT (''),
	[UserPass_N] [varchar](50) NOT NULL CONSTRAINT [DF_UserInfo_UserPass_N]  DEFAULT ('empty'),
	[UserPass2] [varchar](20) NOT NULL CONSTRAINT [DF_UserInfo_UserPass2]  DEFAULT (''),
	[UserPass2_N] [varchar](50) NOT NULL CONSTRAINT [DF_UserInfo_UserPass2_N]  DEFAULT ('empty'),
	[UserType] [int] NOT NULL CONSTRAINT [DF_UserInfo_UserType]  DEFAULT ((1)),
	[UserLoginState] [int] NOT NULL CONSTRAINT [DF_UserInfo_UserLoginState]  DEFAULT ((0)),
	[UserAvailable] [int] NULL CONSTRAINT [DF_UserInfo_UserAvailable]  DEFAULT ((1)),
	[CreateDate] [datetime] NOT NULL CONSTRAINT [DF_UserInfo_CreateDate]  DEFAULT (getdate()),
	[LastLoginDate] [datetime] NOT NULL CONSTRAINT [DF_UserInfo_LastLoginDate]  DEFAULT (getdate()),
	[SGNum] [int] NULL CONSTRAINT [DF_UserInfo_SGNum]  DEFAULT ((0)),
	[SvrNum] [int] NULL CONSTRAINT [DF_UserInfo_SvrNum]  DEFAULT ((0)),
	[ChaName] [varchar](33) NULL CONSTRAINT [DF_UserInfo_ChaName]  DEFAULT (''),
	[UserBlock] [int] NOT NULL CONSTRAINT [DF_UserInfo_UserBlock]  DEFAULT ((0)),
	[UserBlockDate] [datetime] NOT NULL CONSTRAINT [DF_UserInfo_UserBlockDate]  DEFAULT (getdate()),
	[ChaRemain] [int] NOT NULL CONSTRAINT [DF_UserInfo_ChaRemain]  DEFAULT ((4)),
	[ChaTestRemain] [int] NOT NULL CONSTRAINT [DF_UserInfo_ChaTestRemain]  DEFAULT ((4)),
	[PremiumDate] [datetime] NOT NULL CONSTRAINT [DF_UserInfo_PremiumDate]  DEFAULT ('2020-02-01'),
	[ChatBlockDate] [datetime] NOT NULL CONSTRAINT [DF_UserInfo_ChatBlockDate]  DEFAULT ('1970-02-01'),
	[UserPoint] [int] NOT NULL CONSTRAINT [DF_UserInfo_UserPoint]  DEFAULT ((0)),
	[WebLoginState] [varchar](50) NULL,
	[UserAge] [int] NOT NULL CONSTRAINT [DF_UserInfo_UserAge]  DEFAULT ((18)),
	[OfflineTime] [bigint] NOT NULL CONSTRAINT [DF_UserInfo_OfflineTime]  DEFAULT ((-999999999)),
	[GameTime] [bigint] NOT NULL CONSTRAINT [DF_UserInfo_GameTime]  DEFAULT ((-999999999)),
	[UserIP] [varchar](50) NULL,
	[PlayTime] [bigint] NOT NULL CONSTRAINT [DF_UserInfo_PlayTime]  DEFAULT ((0)),
	[UserEmail] [varchar](50) NOT NULL,
	[NameFirst] [varchar](50) NOT NULL CONSTRAINT [DF_UserInfo_NameFirst]  DEFAULT ('empty'),
	[NameLast] [varchar](50) NOT NULL CONSTRAINT [DF_UserInfo_NameLast]  DEFAULT ('empty'),
	[PhoneNumber] [varchar](50) NOT NULL CONSTRAINT [DF_UserInfo_PhoneNumber]  DEFAULT ('empty'),
 CONSTRAINT [PK_UserInfo] PRIMARY KEY CLUSTERED 
(
	[UserNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY],
 CONSTRAINT [IX_UserInfoUserID] UNIQUE NONCLUSTERED 
(
	[UserID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[FullUserInfo]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[FullUserInfo](
	[UserNum] [int] IDENTITY(1,1) NOT NULL,
	[UserName] [varchar](20) NOT NULL CONSTRAINT [DF_FullUserInfo_UserName]  DEFAULT (''),
	[UserID] [varchar](20) NOT NULL CONSTRAINT [DF_FullUserInfo_UserID]  DEFAULT (''),
	[UserPass] [varchar](20) NOT NULL CONSTRAINT [DF_FullUserInfo_UserPass]  DEFAULT (''),
	[UserPass2] [varchar](20) NOT NULL CONSTRAINT [DF_FullUserInfo_UserPass2]  DEFAULT (''),
	[BodyID] [varchar](18) NOT NULL CONSTRAINT [DF_FullUserInfo_BodyID]  DEFAULT (''),
	[Sex] [varchar](2) NOT NULL,
	[Email] [varchar](50) NOT NULL,
	[BirthY] [varchar](4) NOT NULL,
	[BirthM] [varchar](2) NOT NULL,
	[BirthD] [varchar](2) NOT NULL,
	[TEL] [varchar](15) NOT NULL,
	[Mobile] [varchar](13) NULL,
	[QQ] [varchar](13) NULL,
	[MSN] [varchar](50) NULL,
	[City1] [varchar](20) NOT NULL,
	[City2] [varchar](20) NOT NULL,
	[Post] [varchar](6) NULL,
	[Address] [varchar](60) NULL,
	[SafeId] [varchar](12) NOT NULL
) ON [PRIMARY]
SET ANSI_PADDING OFF
ALTER TABLE [dbo].[FullUserInfo] ADD [BodyID2] [varchar](18) NULL
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[CheckId]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[CheckId](
	[Num] [int] IDENTITY(1,1) NOT NULL,
	[Id] [varchar](18) NOT NULL,
	[CreateDate] [datetime] NULL,
 CONSTRAINT [PK_CheckId] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[BlockAddress]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[BlockAddress](
	[BlockIdx] [int] IDENTITY(1,1) NOT NULL,
	[BlockAddress] [varchar](23) NOT NULL,
	[BlockReason] [varchar](256) NULL,
	[BlockDate] [datetime] NULL CONSTRAINT [DF_BlockAddress_BlockDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_BlockAddress] PRIMARY KEY CLUSTERED 
(
	[BlockIdx] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[IPInfo]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[IPInfo](
	[IpAddress] [varchar](23) NOT NULL,
	[UserNum] [int] NOT NULL,
	[IdxIP] [int] IDENTITY(1,1) NOT NULL,
	[UseAvailable] [int] NULL,
 CONSTRAINT [PK_IPInfo] PRIMARY KEY CLUSTERED 
(
	[IdxIP] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[gmc]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[gmc](
	[username] [nvarchar](50) NULL,
	[session] [varchar](max) NULL,
	[sesexp] [varchar](max) NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Vote]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Vote](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[UserID] [varchar](20) NOT NULL CONSTRAINT [DF_VoteTime_UserName]  DEFAULT (''),
	[last_vote] [int] NULL,
	[date] [datetime] NOT NULL CONSTRAINT [DF_VoteTime_date]  DEFAULT ('1970-02-01'),
	[hits] [int] NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[StatLogin]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[StatLogin](
	[LYear] [int] NOT NULL CONSTRAINT [DF_StatLogin_LYear]  DEFAULT (datepart(year,getdate())),
	[LMonth] [int] NOT NULL CONSTRAINT [DF_StatLogin_LMonth]  DEFAULT (datepart(month,getdate())),
	[LDay] [int] NOT NULL CONSTRAINT [DF_StatLogin_LDay]  DEFAULT (datepart(day,getdate())),
	[LHour] [int] NOT NULL CONSTRAINT [DF_StatLogin_LHour]  DEFAULT (datepart(hour,getdate())),
	[LCount] [int] NULL CONSTRAINT [DF_StatLogin_LCount]  DEFAULT ((1)),
 CONSTRAINT [PK_StatLogin] PRIMARY KEY CLUSTERED 
(
	[LYear] ASC,
	[LMonth] ASC,
	[LDay] ASC,
	[LHour] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[StatGameTime]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[StatGameTime](
	[GYear] [int] NOT NULL CONSTRAINT [DF_StatGameTime_GYear]  DEFAULT (datepart(year,getdate())),
	[GMonth] [int] NOT NULL CONSTRAINT [DF_StatGameTime_GMonth]  DEFAULT (datepart(month,getdate())),
	[GDay] [int] NOT NULL CONSTRAINT [DF_StatGameTime_GDay]  DEFAULT (datepart(day,getdate())),
	[GTime] [int] NULL CONSTRAINT [DF_StatGameTime_GCount]  DEFAULT ((0)),
 CONSTRAINT [PK_StatGameTime] PRIMARY KEY CLUSTERED 
(
	[GYear] ASC,
	[GMonth] ASC,
	[GDay] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ServerInfo]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ServerInfo](
	[SGNum] [int] NOT NULL,
	[SvrNum] [int] NOT NULL,
	[SvrType] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[SvrNum] ASC,
	[SGNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  View [dbo].[viewServerList]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO
-------------------------------------------------------------------------------
-- view_ServerList.sql
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewServerList]
AS
SELECT  A.SGNum, A.SvrNum, A.SvrType, B.SGName, 
        B.OdbcName, B.OdbcUserID, B.OdbcPassword,
        B.OdbcLogName, B.OdbcLogUserID, B.OdbcLogPassword
FROM    dbo.ServerInfo A LEFT OUTER JOIN
        dbo.ServerGroup B ON A.SGNum = B.SGNum
WHERE   (A.SvrType = 4)
GO
/****** Object:  StoredProcedure [dbo].[log_serverstate]    Script Date: 10/25/2015 16:52:54 ******/
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
/****** Object:  StoredProcedure [dbo].[user_logout]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE Procedure [dbo].[user_logout]
    @userId     char(25),
    @usernum int,
    @gametime int,
    @chanum   int,
    @svrgrp   int,
    @svrnum   int,
    @extra   int,
    @nReturn  int OUTPUT

AS
    SET NOCOUNT ON

    DECLARE 
        -- Declare variables used in error checking.
        @error_var int, 
        @rowcount_var int
    
    -- ???, ??? ????? ??
    UPDATE UserInfo
    SET UserLoginState=0, LastLoginDate=getdate() 
    WHERE UserNum = @usernum
    
    -- ???? ??? 1 : ??? 0 : ????
    INSERT INTO LogLogin (UserNum, UserID, LogInOut) 
    VALUES (@usernum, @userId, 0)
    
    -- ???? ??? 
    INSERT INTO LogGameTime (UserNum, UserID, GameTime, ChaNum, SGNum, SvrNum) 
    VALUES (@usernum, @userId, @gametime, @chanum, @svrgrp, @svrnum)


	UPDATE UserInfo
    SET PlayTime=PlayTime+@gametime 
    WHERE usernum = @usernum


    -- ???? ?? ????
    UPDATE StatGameTime
    SET GTime=GTime+@gametime 
    WHERE GYear=Year(GetDate()) AND GMonth=Month(GetDate()) AND GDay=Day(GetDate())

    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        INSERT INTO StatGameTime (GYear, GMonth, GDay, GTime)  
        VALUES (Year(GetDate()), Month(GetDate()), Day(GetDate()), @gametime)
    END

    SET NOCOUNT OFF
GO
/****** Object:  View [dbo].[viewLogLogin]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-------------------------------------------------------------------------------
-- viewLogLogin
-------------------------------------------------------------------------------
Create view [dbo].[viewLogLogin] AS
SELECT  LoginNum, UserNum, UserID, LogInOut, LogDate, LogIpAddress
FROM LogLogin
GO
/****** Object:  StoredProcedure [dbo].[user_verify]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[user_verify]
    @userId        char(25),
    @userPass     char(25),
    @userIp        char(25),
    @SvrGrpNum    int,
    @SvrNum        int,   
    @proPass    varchar(6), -- Ran dynamic password
    @proNum     varchar(2), -- Ran dynamic password random number
    @nReturn     int    OUTPUT

AS        
    DECLARE 
        @nAvailable    int,
        @nUserNum    int,
        @nState int,
        -- Declare variables used in error checking.
        @error_var int, 
        @rowcount_var int,
        @nBlock int,
        @BlockDate datetime,
        @EndDate datetime,
        @StrSql nvarchar(100)
 
    SET NOCOUNT ON

    SET @nReturn = 0
    SET @nUserNum = 0
    
    SELECT @nUserNum=UserInfo.UserNum, 
           @nState=UserInfo.UserLoginState, 
           @nBlock=UserInfo.UserBlock, 
           @BlockDate=UserInfo.UserBlockDate

    FROM UserInfo
    WHERE UserID = @userId AND UserPass = @userPass AND UserAvailable = 1


    -----------------------------------------------------------------
-- ID / PWD check...
    IF @nUserNum = 0
    BEGIN        
        SET @nReturn = 0        
        RETURN @nReturn
    END
    ELSE
    BEGIN        
        SET @nReturn = 1        
        IF @nState = 1
        BEGIN
            SET @nReturn = 5
             RETURN @nReturn 
--	update userinfo set userloginstate =0
--	where usernum =@nUserNum 
       END
    END


    IF (SELECT COUNT(*) FROM BlockAddress WITH (NOLOCK) WHERE BlockAddress = @userIp) > 0

    BEGIN
        declare @params as nvarchar(100)        
        SET @StrSQL = 'SELECT @ordercnt=count(userid) FROM Randpass WHERE userid='''+@userId+''' AND pwd'+@proNum + '='''+@proPass + ''''
        SET @params = '@ordercnt as int OUTPUT' -- OUTPUT ???? ??
        
        exec sp_executesql @StrSQL, @params, @ordercnt = @rowcount_var OUTPUT

        SELECT @error_var = @@ERROR
        IF @error_var = 0 AND @rowcount_var = 1
        BEGIN
            SET @nReturn = 1 -- Dynamic password correct
        END
        ELSE
        BEGIN
            SET @nReturn = 7 -- Dynamic password error            
            RETURN @nReturn            
        END        
    END


    -----------------------------------------------------------------
    -- IP Address ??
    IF (SELECT COUNT(*) FROM IPInfo WITH (NOLOCK) WHERE ipAddress = @userIp) > 0
    -- IP ?? ??
    BEGIN
        SELECT @nAvailable = useAvailable 
        FROM IPInfo 
        WHERE ipAddress = @userIp
        
        IF @nAvailable = 1 
        BEGIN            
            SET @nReturn = 2 -- ID/PWD ? ????, IP ? ????            
        END
        ELSE
        BEGIN            
            SET @nReturn = 4 -- ID/PWD ? ????, IP ? ????? ??            
        END
    END
    ELSE
    -- IP ?? ??
    BEGIN
        SET @nReturn = 3     -- ID/PWD ? ????, IP ??? ??        
    END

    -----------------------------------------------------------------
    -- Block ?? ??
    IF (@nBlock = 1)
    BEGIN
        IF (@BlockDate > GetDate())
        BEGIN
            SET @nReturn = 6
        END
        ELSE
        BEGIN
            UPDATE UserInfo 
            SET UserBlock=0 
            WHERE UserNum = @nUserNum
            
            SET @nReturn  = 2
        END 
    END    
    
    -----------------------------------------------------------------
    -- ??? ???? ??    
    IF (@nReturn = 1) OR (@nReturn = 2) OR (@nReturn = 3)
    BEGIN
        -- ???, ??? ????? ??
        UPDATE UserInfo
        SET UserLoginState=1, LastLoginDate=getdate(), SGNum=@SvrGrpNum, SvrNum=@SvrNum 
        WHERE UserNum = @nUserNum
        
        -- ???? ???
        INSERT INTO LogLogin (UserNum, UserID, LogInOut, LogIpAddress) 
        VALUES (@nUserNum, @userId, 1, @userIp)    
        
        -- ?? ????
        UPDATE StatLogin
        SET LCount = LCount+1 
        WHERE LYear=Year(GetDate()) AND LMonth=Month(GetDate()) AND LDay=Day(GetDate()) AND LHour=DatePart(hour, GetDate())
        
        SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
        IF @error_var <> 0 OR @rowcount_var = 0
        BEGIN
            INSERT INTO StatLogin (LYEAR) 
            VALUES (YEAR(GetDate()))
        END
    END

    SET NOCOUNT OFF    
    
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[gm_login]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO
-------------------------------------------------------------------------------
-- sp_gm_login.sql
-------------------------------------------------------------------------------
CREATE PROCEDURE [dbo].[gm_login]
	@userId		char(50),
	@userPass 	char(50),
	@authenticate char(50),
	@nReturn 	int	OUTPUT
AS
	DECLARE @nUserNum	int,
		@nUserType	int

	SET NOCOUNT ON

	SET @nReturn = 0
	SET @nUserNum = 0
	
	SELECT @nUserNum = UserInfo.UserNum, @nUserType=UserInfo.UserType 
	FROM UserInfo 
	WHERE UserID = @userId AND UserPass = @userPass AND UserAvailable = 1 AND UserType>=20 

	-- ID / PWD ??...
	IF @nUserNum = 0
	BEGIN
		-- ID / PWD ??? ?? ???????
		SET @nReturn = 0
	END
	ELSE
	BEGIN
		-- ID / PWD ??
		SET @nReturn = @nUserType
		-- ???? ???
		INSERT INTO LogGmCmd (UserNum, GmCmd) 
		VALUES (@nUserNum, 'LOGIN GMTOOL UserID:' + @userId)
	END	

	SET NOCOUNT OFF	
	
	RETURN @nReturn
GO
/****** Object:  View [dbo].[viewLogGameTime]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-------------------------------------------------------------------------------
-- viewLogGameTime
-------------------------------------------------------------------------------
CREATE VIEW [dbo].[viewLogGameTime] AS
SELECT GameTimeNum, LogDate, GameTime, UserID, UserNum, SGNum, SvrNum, ChaNum
FROM LogGameTime
GO
/****** Object:  StoredProcedure [dbo].[UserLogoutSimple2]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UserLogoutSimple2]
	@nUserNum int
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET UserLoginState=0 
	WHERE UserNum=@nUserNum

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[UserLogoutSimple]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UserLogoutSimple]
	@szUserID varchar(20)
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET UserLoginState=0 
	WHERE UserID=@szUserID

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[user_register]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[user_register]
    @userId				char(25),
    @userPass1			char(25),
	@userPass2			char(25),
	@userPass1_n		char(25),
	@userPass2_n		char(25),
	@userMail			char(50),
	@userNameFirst		char(25),
	@userNameLast		char(25),
	@userPhoneNumber	char(25),
    @SvrGrpNum			int,
    @SvrNum				int,   
    @nReturn			int    OUTPUT

AS        
    DECLARE 
		@nUserNum int,
        @error_var int,
        @rowcount_var int

    SET NOCOUNT ON

    SET @nReturn = 0
    SET @nUserNum = 0
    
    SELECT @nUserNum=UserInfo.UserNum
           
    FROM UserInfo
    WHERE UserID = @userId

    IF @nUserNum > 0
    BEGIN    
		 /*user exist*/    
        SET @nReturn = 1       
        RETURN @nReturn 
    END
	ELSE
		BEGIN TRAN

		INSERT INTO UserInfo ( UserName, UserID, UserPass, UserPass_N, UserPass2, UserPass2_N, UserEmail, NameFirst, NameLast, PhoneNumber, SGNum, SvrNum )
		VALUES (	@userId, @userId, @userPass1, @userPass1_n, @userPass2, @userPass2_n, @userMail, @userNameFirst, @userNameLast, @userPhoneNumber,  @SvrGrpNum, @SvrNum )
	
		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
		IF @error_var <> 0 OR @rowcount_var = 0
			BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
			END
		ELSE
			BEGIN
			COMMIT TRAN
			END

   
    SET NOCOUNT OFF    
    
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[user_gettype]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[user_gettype]
	@nUserNum	int,
	@nReturn 	int	OUTPUT
AS	
    
	DECLARE @nUserType int

	SET NOCOUNT ON

	SET @nReturn = 0
	SET @nUserType = 0
	
	SELECT @nUserType = UserInfo.UserType 
	FROM UserInfo
	WHERE UserNum = @nUserNum
	
	SET @nReturn = @nUserType

	SET NOCOUNT OFF	
	
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[user_cha_test_remain]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[user_cha_test_remain]
	@nUserNum	int,
	@nReturn 	int	OUTPUT
AS	    
	DECLARE @nChaRemain int

	SET NOCOUNT ON

	SET @nReturn = 0
	
	SELECT @nChaRemain = UserInfo.ChaTestRemain
	FROM UserInfo
	WHERE UserNum = @nUserNum
	
	SET @nReturn = @nChaRemain

	SET NOCOUNT OFF	
	
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[user_cha_remain]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[user_cha_remain]
	@nUserNum	int,
	@nReturn 	int	OUTPUT
AS	    
	DECLARE @nChaRemain int

	SET NOCOUNT ON

	SET @nReturn = 0
	SET @nChaRemain = 0
	
	SELECT @nChaRemain = UserInfo.ChaRemain
	FROM UserInfo
	WHERE UserNum = @nUserNum
	
	SET @nReturn = @nChaRemain

	SET NOCOUNT OFF	
	
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[UpdateTestChaNumIncrease]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateTestChaNumIncrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaTestRemain=ChaTestRemain+1
	WHERE UserNum=@nUserNum	
	
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
/****** Object:  StoredProcedure [dbo].[UpdateTestChaNumDecrease]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateTestChaNumDecrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaTestRemain=ChaTestRemain-1
	WHERE UserNum=@nUserNum	
	
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
/****** Object:  StoredProcedure [dbo].[UpdateChaNumIncrease]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaNumIncrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaRemain=ChaRemain+1
	WHERE UserNum=@nUserNum	
	
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
/****** Object:  StoredProcedure [dbo].[UpdateChaNumDecrease]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaNumDecrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaRemain=ChaRemain-1
	WHERE UserNum=@nUserNum
	
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
/****** Object:  StoredProcedure [dbo].[UpdateChaName]    Script Date: 10/25/2015 16:52:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateChaName]
	@nUserNum int,
	@szChaName varchar (33)
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET ChaName=@szChaName
	WHERE UserNum=@nUserNum
	
	SET NOCOUNT OFF
GO
