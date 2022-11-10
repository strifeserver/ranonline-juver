USE [RanUser]
GO
/****** Object:  StoredProcedure [dbo].[UserLogoutSimple]    Script Date: 05/07/2017 14:37:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER PROCEDURE [dbo].[UserLogoutSimple]
	@szUserID varchar(20)
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET UserLoginState=0 
	WHERE UserID=@szUserID

	---PCID
	DELETE FROM UserKey 
	WHERE PCIDUserID=@szUserID
	
	SET NOCOUNT OFF
