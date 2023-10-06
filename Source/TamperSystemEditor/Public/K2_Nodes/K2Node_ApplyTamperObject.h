// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_ConstructObjectFromClass.h"
#include "K2Node_ApplyTamperObject.generated.h"

/**
 * 
 */
UCLASS()
class TAMPERSYSTEMEDITOR_API UK2Node_ApplyTamperObject : public UK2Node_ConstructObjectFromClass
{
	GENERATED_BODY()
public:

	UK2Node_ApplyTamperObject();
    	
    virtual void AllocateDefaultPins() override;
    virtual FText GetBaseNodeTitle() const override;
    virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;
    virtual FText GetDefaultNodeTitle() const override;
    virtual FText GetNodeTitleFormat() const override;
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual UClass* GetClassPinBaseClass() const override;
    virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const override;
    virtual FText GetMenuCategory() const override;
    virtual FName GetCornerIcon() const override;
    
    /** Make a pin for the TamperSystem component to own the Tamper Object */
    UEdGraphPin* GetTamperSystemPin() const;
    virtual void CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins) override;
    
    
    //~ Begin UEdGraphNode Interface.
    virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
    virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;
    virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;
    //~ End UEdGraphNode Interface.

    virtual bool UseWorldContext() const override { return false; }
    virtual bool UseOuter() const override { return false; }

};
