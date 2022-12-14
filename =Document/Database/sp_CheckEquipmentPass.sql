USE [RanGame1]
GO
/****** Object:  StoredProcedure [dbo].[sp_CheckEquipmentPass]    Script Date: 01/16/2018 17:11:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


ALTER PROCEDURE [dbo].[sp_CheckEquipmentPass]
	@nChaNum int,
	@szChaName varchar(33),
	@szChaEPass varchar(4),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nNum int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nNum = 0

	SELECT @nNum=ChaEquipmentPass.Num    
    FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum AND ChaName = @szChaName AND ChaEPass = @szChaEPass

    IF @nNum > 0
    BEGIN
		--found
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn  
    END
    ELSE
    BEGIN
		--not found
        SET @nReturn = 1  
        SET NOCOUNT OFF     
        RETURN @nReturn 
    END