USE [RanGame1]
GO
/****** Object:  StoredProcedure [dbo].[sp_DeleteEquipmentPass]    Script Date: 01/18/2018 16:17:30 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_DeleteEquipmentPass]
	@nChaNum int,
	@szChaName varchar(33),
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
    WHERE ChaNum = @nChaNum AND ChaName = @szChaName

    IF @nNum = 0
    BEGIN    
		 --data not exist
        SET @nReturn = -1   
        SET NOCOUNT OFF    
        RETURN @nReturn 
    END
    
    -- delete entry
    DELETE FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum AND ChaName = @szChaName
    
    -- remove charinfo locks
    UPDATE ChaInfo 
    SET ChaEquipmentLockEnable = 0, ChaEquipmentLockStatus = 0 
    WHERE ChaNum=@nChaNum 
        
    SET @nReturn = 0
    SET NOCOUNT OFF
    RETURN @nReturn 