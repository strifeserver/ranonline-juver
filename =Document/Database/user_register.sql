USE [RanUser]
GO
/****** Object:  StoredProcedure [dbo].[user_register]    Script Date: 11/23/2017 16:02:05 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[user_register]
    @userId				varchar(25),
    @userPass1			varchar(25),
	@userPass2			varchar(25),
	@userSA				varchar(25),
	@userMail			varchar(50),
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

		INSERT INTO UserInfo ( UserName, UserID, UserPass, UserPass2, UserSA, UserEmail, SGNum, SvrNum )
		VALUES (	@userId, @userId, @userPass1, @userPass2, @userSA, @userMail, @SvrGrpNum, @SvrNum )
	
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



