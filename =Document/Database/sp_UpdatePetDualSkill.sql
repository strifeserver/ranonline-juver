set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
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


