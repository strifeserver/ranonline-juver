USE [RanUser]
GO
/****** Object:  StoredProcedure [dbo].[user_verify]    Script Date: 05/07/2017 17:48:16 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



ALTER PROCEDURE [dbo].[user_verify]
    @userId        char(25),
    @userPass     char(25),
    @userIp        char(25),
    @SvrGrpNum    int,
    @SvrNum        int,   
    @proPass    varchar(6), -- Ran dynamic password
    @proNum     varchar(2), -- Ran dynamic password random number
    @pcID  varchar(33), --PCID
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
        @StrSql nvarchar(100),
        @LastLoginDate datetime,
        @UserLevel int
 
    SET NOCOUNT ON

    SET @nReturn = 0
    SET @nUserNum = 0
    
    SELECT @nUserNum=UserInfo.UserNum, 
           @nState=UserInfo.UserLoginState, 
           @nBlock=UserInfo.UserBlock, 
           @BlockDate=UserInfo.UserBlockDate,
           @LastLoginDate=UserInfo.LastLoginDate,
           @UserLevel = UserInfo.UserType

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

	---------
	---Login delay check
	---works only on non user gm
	IF @UserLevel < 20
	BEGIN
		IF (SELECT DATEDIFF(SECOND, @LastLoginDate, GETDATE()) ) < 20
		BEGIN
			SET @nReturn = 30
			RETURN @nReturn
		END
	END 
	
	---PCID
	---comment this lines to allow multi login per pc
	IF (SELECT COUNT(*) FROM UserKey WITH (NOLOCK) WHERE PCIDKey = @pcID ) > 0
	BEGIN
		-- pc active
		SET @nReturn = 31
		RETURN @nReturn
	END
	
	INSERT INTO UserKey (PCIDKey,PCIDUserNum,PCIDUserID,PCIDSGNum) VALUES (@pcID, @nUserNum, @userId, @SvrGrpNum )
	---END PCID
	
	
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



