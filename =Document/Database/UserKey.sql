USE [RanUser]
GO

/****** Object:  Table [dbo].[UserKey]    Script Date: 05/07/2017 17:47:44 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[UserKey](
	[Num] [int] IDENTITY(1,1) NOT NULL,
	[PCIDKey] [varchar](33) NOT NULL,
	[PCIDUserNum] [int] NOT NULL,
	[PCIDUserID] [varchar](20) NOT NULL,
	[PCIDSGNum] [int] NOT NULL
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_MacKey]  DEFAULT ('') FOR [PCIDKey]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_UserNum]  DEFAULT ((0)) FOR [PCIDUserNum]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_MacUserID]  DEFAULT ('') FOR [PCIDUserID]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDSGNum]  DEFAULT ((0)) FOR [PCIDSGNum]
GO


