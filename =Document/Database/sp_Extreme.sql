USE [RanGame1]
GO
/****** Object:  StoredProcedure [dbo].[sp_Extreme]    Script Date: 12/22/2016 11:07:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- ??? ?/? ?? ??? ????.
ALTER   PROCEDURE [dbo].[sp_Extreme]
	@nUserNum	int

AS	
	DECLARE
		@error_var int, 
		@rowcount_var int	

	SET NOCOUNT ON
Select (MSum-MS) As M, (FSum-FS) As F
From
(
	Select isnull(Sum(M),0) As MSum, isnull(Sum(F),0) As FSum, isnull(Sum(MS),0) As MS, isnull(Sum(FS),0) As FS
	From
	(
	Select ChaClass
	,
	Case ChaClass
	When 1 Then 1
	When 2 Then 1
	When 256 Then 1
	When 512 Then 1
	When 1024 Then 1
	When 4096 Then 1
	When 16384 Then 1
	Else 0
	End As M
	,
	Case ChaClass
	When 4 Then 1
	When 8 Then 1
	When 64 Then 1
	When 128 Then 1
	When 2048 Then 1
	When 8192 Then 1
	When 32768 Then 1
	Else 0
	End As F
	,
	Case ChaClass
	When 16 Then 
		Case ChaDeleted
		When 1 Then 0
		Else 1
		End
	Else 0
	End As MS
	,
	Case ChaClass
	When 32 Then 
		Case ChaDeleted
		When 1 Then 0
		Else 1
		End
	Else 0
	End As FS
	From ChaInfo Where UserNum=@nUserNum And (
	( ChaClass=16 OR ChaClass=32 ) 
	OR ( ( ChaClass=1 OR ChaClass=2 OR ChaClass=4 OR ChaClass=8 OR ChaClass=64 OR ChaClass=128 OR ChaClass=256 OR ChaClass=512 OR ChaClass=1024 OR ChaClass=2048 OR ChaClass=4096 OR ChaClass=8192 OR ChaClass=16384 OR ChaClass=32768 ) AND ChaLevel>=190 ) )
	) As t
) As tt
