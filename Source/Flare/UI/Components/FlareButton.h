#pragma once

#include "../../Flare.h"


DECLARE_DELEGATE(FFlareButtonClicked)


class SFlareButton : public SCompoundWidget
{
	/*----------------------------------------------------
		Slate arguments
	----------------------------------------------------*/

	SLATE_BEGIN_ARGS(SFlareButton)
		: _Color(FLinearColor::White)
		, _Toggle(false)
		, _Width(5)
		, _Height(1)
	{}

	SLATE_EVENT(FFlareButtonClicked, OnClicked)

	SLATE_ATTRIBUTE(FText, Text)
	SLATE_ATTRIBUTE(FText, ToolTipText)
	SLATE_ATTRIBUTE(const FSlateBrush*, Icon);
	SLATE_ATTRIBUTE(FSlateColor, Color)

	SLATE_ARGUMENT(bool, Toggle)
	SLATE_ARGUMENT(int32, Width)
	SLATE_ARGUMENT(int32, Height)
	
	SLATE_END_ARGS()


public:

	/*----------------------------------------------------
		Public methods
	----------------------------------------------------*/

	/** Create the widget */
	void Construct(const FArguments& InArgs);

	/** Set the toggle state */
	void SetActive(bool State);

	/** Get the toggle state */
	bool IsActive() const;

	/** Brush callback */
	const FSlateBrush* GetDecoratorBrush() const;

	/** Brush callback*/
	const FSlateBrush* GetBackgroundBrush() const;

	/** Color callback */
	FSlateColor GetMainColor() const;

	/** Mouse click	*/
	FReply OnButtonClicked();


protected:

	/*----------------------------------------------------
		Private data
	----------------------------------------------------*/

	// State data
	bool                           IsToggle;
	bool                           IsPressed;
	
	// Slate data
	FFlareButtonClicked            OnClicked;
	TSharedPtr<SBorder>            InnerContainer;
	TAttribute<const FSlateBrush*> Icon;
	TAttribute<FSlateColor>        Color;


public:

	/*----------------------------------------------------
		Get & Set
	----------------------------------------------------*/

	TSharedPtr<SBorder> GetContainer() const
	{
		return InnerContainer;
	}


};
