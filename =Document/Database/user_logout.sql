USE [RanUser]
GO
/****** Object:  StoredProcedure [dbo].[user_logout]    Script Date: 05/07/2017 14:37:37 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO




ALTER Procedure [dbo].[user_logout]
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
	
	---PCID
	DELETE FROM UserKey 
	WHERE PCIDUserNum=@usernum

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



