USE [RanGame1]
GO
/****** Object:  StoredProcedure [dbo].[sp_ChangeEquipmentPass]    Script Date: 01/18/2018 10:41:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_ChangeEquipmentPass]
	@nChaNum int,
	@szChaName varchar(33),
	@szChaEPass varchar(4),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nNum int,
		@nCharNum int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nNum = 0
	SET @nCharNum = 0

	SELECT @nNum=ChaEquipmentPass.Num    
    FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum AND ChaName = @szChaName

    IF @nNum = 0
    BEGIN    
		 --data not exist
        SET @nReturn = 1   
        SET NOCOUNT OFF    
        RETURN @nReturn 
    END
    
	--update epass
    UPDATE ChaEquipmentPass
    SET ChaEPass=@szChaEPass
    WHERE ChaNum=@nChaNum AND ChaName = @szChaName

    
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