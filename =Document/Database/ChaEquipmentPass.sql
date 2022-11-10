USE [RanGame1]
GO

/****** Object:  Table [dbo].[ChaEquipmentPass]    Script Date: 01/14/2018 19:43:03 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[ChaEquipmentPass](
	[Num] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[ChaName] [varchar](33) NOT NULL,
	[ChaEPass] [varchar](4) NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_ChaEquipmentPass] PRIMARY KEY CLUSTERED 
(
	[Num] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[ChaEquipmentPass] ADD  CONSTRAINT [DF_ChaEquipmentPass_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO

ALTER TABLE [dbo].[ChaEquipmentPass] ADD  CONSTRAINT [DF_ChaEquipmentPass_ChaName]  DEFAULT ('') FOR [ChaName]
GO

ALTER TABLE [dbo].[ChaEquipmentPass] ADD  CONSTRAINT [DF_Table_1_ChaEPin]  DEFAULT ('') FOR [ChaEPass]
GO

ALTER TABLE [dbo].[ChaEquipmentPass] ADD  CONSTRAINT [DF_ChaEquipmentPass_SetDate]  DEFAULT (getdate()) FOR [Date]
GO


