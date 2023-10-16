// Fill out your copyright notice in the Description page of Project Settings.


#include "K2_Nodes/K2Node_ApplyTamperObject.h"
#include "Kismet/GameplayStatics.h"
#include "K2Node_CallFunction.h"
#include "KismetCompilerMisc.h"
#include "KismetCompiler.h"
#include "EdGraphSchema_K2.h"
#include "FunctionLibraries/TamperBlueprintFunctionLibrary.h"
#include "GameFramework/TamperObject.h"
#include "UObject/ObjectSaveContext.h"

#define LOCTEXT_NAMESPACE "K2Node_ApplyTamperObject"

#define TAMPERPIN TEXT("TamperSystem")
#define WORLD_CONTEXT_PIN TEXT("WorldContextObject")
#define TAMPERCLASSPIN TEXT("Class")

UK2Node_ApplyTamperObject::UK2Node_ApplyTamperObject()
{
	NodeTooltip = LOCTEXT("NodeTooltip", "Attempts to apply a new Tamper Object to the target");
}

void UK2Node_ApplyTamperObject::AllocateDefaultPins()
{
	// Add execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	// Add the Output Object
	UEdGraphPin* OutputPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, GetClassPinBaseClass(), UEdGraphSchema_K2::PN_ReturnValue);

	// If required add the world context pin
	if (UseWorldContext())
	{
		CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), WORLD_CONTEXT_PIN);
	}

	// Add blueprint pin
	UEdGraphPin* ClassPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, GetClassPinBaseClass(), TAMPERCLASSPIN);
	
	TArray<UEdGraphPin*> ClassPins;
	const TArray<UEdGraphPin*> InClassPin = {ClassPin};
	CreatePinsForClass(GetClassPinBaseClass(), &ClassPins);
	
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* TamperSystemPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(),TAMPERPIN);
}

FText UK2Node_ApplyTamperObject::GetBaseNodeTitle() const
{
	return LOCTEXT("AddTamper", "Add Tamper Of Class");
}

void UK2Node_ApplyTamperObject::GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const
{
	if (UEdGraphPin* ClassPin = GetClassPin())
 	{
 		SetPinToolTip(*ClassPin, LOCTEXT("ClassPinDescription", "The Tamper class you want to add to the target Tamper system"));
 	}
 	if (UEdGraphPin* ResultPin = GetResultPin())
 	{
 		SetPinToolTip(*ResultPin, LOCTEXT("ResultPinDescription", "The newly constructed Tamper object"));
 	}
 	if (UEdGraphPin* TamperSystemPin = GetTamperSystemPin())
 	{
 		SetPinToolTip(*TamperSystemPin, LOCTEXT("OuterPinDescription", "Tamper system that receives the constructed Tamper object"));
 	}
 
 	return UK2Node::GetPinHoverText(Pin, HoverTextOut);
}

FText UK2Node_ApplyTamperObject::GetDefaultNodeTitle() const
{
 return  GetBaseNodeTitle();
}

FText UK2Node_ApplyTamperObject::GetNodeTitleFormat() const
{
	return LOCTEXT("AddTamper", "Add [{ClassName}] Tamper To [{TamperSystem}]");
}

FLinearColor UK2Node_ApplyTamperObject::GetNodeTitleColor() const
{
	return FLinearColor( 168, 0, 146 );
}

UClass* UK2Node_ApplyTamperObject::GetClassPinBaseClass() const
{
	return UTamperObject::StaticClass();
}

bool UK2Node_ApplyTamperObject::IsSpawnVarPin(UEdGraphPin* Pin) const
{
	return (Super::IsSpawnVarPin(Pin) && Pin->PinName != TAMPERPIN);
}

FText UK2Node_ApplyTamperObject::GetMenuCategory() const
{
	return NSLOCTEXT("TamperSystem", "Tamper System", "Tamper System");
}

FName UK2Node_ApplyTamperObject::GetCornerIcon() const
{
	return TEXT("Graph.Replication.AuthorityOnly");
}

UEdGraphPin* UK2Node_ApplyTamperObject::GetTamperSystemPin() const
{
	UEdGraphPin* Pin = FindPin(TAMPERPIN);
	check(Pin == NULL || Pin->Direction == EGPD_Input);
	return Pin;
}

void UK2Node_ApplyTamperObject::CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins)
{
	Super::CreatePinsForClass(InClass, OutClassPins);
}

void UK2Node_ApplyTamperObject::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* Schema = CompilerContext.GetSchema();
		
	// This Node: Input pins
	UEdGraphPin* ThisNode_ExecPin = GetExecPin();
	UEdGraphPin* ThisNode_ClassPin = GetClassPin();
	UEdGraphPin* ThisNode_TamperSystemPin = GetTamperSystemPin();
	
	// This Node: output pins
	UEdGraphPin* ThisNode_ThenPin = GetThenPin();	
	UEdGraphPin* ThisNode_ResultPin = GetResultPin();

	/*
	 * Firstly we need to create the Tamper object
	 */
	
	// Create the CreateTamper node.
	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UTamperBlueprintFunctionLibrary, AddTamper), UTamperBlueprintFunctionLibrary::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	// Create Node: Input pins
	UEdGraphPin* CreateNode_ExecPin = CallCreateNode->GetExecPin();
	UEdGraphPin* CreateNode_ClassPin = CallCreateNode->FindPin(TAMPERCLASSPIN);
	UEdGraphPin* CreateNode_TamperSystemPin = CallCreateNode->FindPin(TAMPERPIN);

	// Create Node: Output pins
	UEdGraphPin* CreateNode_ResultPin = CallCreateNode->GetReturnValuePin();
	CreateNode_ResultPin->PinType = ThisNode_ResultPin->PinType; // Casting hack

	/*
	 * Then we need to fill out the default values (ExposeOnSpawn)
	 */
	UEdGraphPin* AssigmentNodes_ThenPin = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, this, CreateNode_ResultPin, GetClassToSpawn());

	

	// Create the RegisterTamper node.
	// UK2Node_CallFunction* CallRegisterNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	// CallRegisterNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UTamperBlueprintFunctionLibrary, RegisterTamperObject), UTamperBlueprintFunctionLibrary::StaticClass());
	// CallRegisterNode->AllocateDefaultPins();
	
	// Register Node: Input pins
	// UEdGraphPin* RegisterNode_ExecPin = CallRegisterNode->GetExecPin();
	// UEdGraphPin* RegisterNode_TamperPin = CallRegisterNode->FindPin(TAMPERCLASSPIN);
	
	// Register Node: Output pins
	// UEdGraphPin* RegisterNode_ThenPin = CallRegisterNode->GetThenPin();
	// UEdGraphPin* RegisterNode_ResultPin = CallRegisterNode->GetReturnValuePin();
	// RegisterNode_ResultPin->PinType = ThisNode_ResultPin->PinType;

	/*
	 * Wire the pins
	 */
	// AssigmentNodes_ThenPin->MakeLinkTo(RegisterNode_ExecPin);
	// CreateNode_ResultPin->MakeLinkTo(RegisterNode_TamperPin);

	/*
	 * Move the wiring outside and expand the node
	 */
	// Move the pins to the intermediate nodes. (This expands the node by their pins.)
	CompilerContext.MovePinLinksToIntermediate(*ThisNode_ExecPin, *CreateNode_ExecPin);
	CompilerContext.MovePinLinksToIntermediate(*ThisNode_ClassPin, *CreateNode_ClassPin);
	CompilerContext.MovePinLinksToIntermediate(*ThisNode_TamperSystemPin, *CreateNode_TamperSystemPin);

	// CompilerContext.MovePinLinksToIntermediate(*ThisNode_ThenPin, *RegisterNode_ThenPin);
	// CompilerContext.MovePinLinksToIntermediate(*ThisNode_ResultPin, *RegisterNode_ResultPin);
	
	// Break all internal pins, so we can clean up?
	BreakAllNodeLinks();

	
	
}

void UK2Node_ApplyTamperObject::EarlyValidation(FCompilerResultsLog& MessageLog) const
{
	Super::EarlyValidation(MessageLog);
	UEdGraphPin* ClassPin = GetClassPin(&Pins);
	const bool bAllowAbstract = ClassPin && ClassPin->LinkedTo.Num();
	UClass* ClassToSpawn = GetClassToSpawn();
	
	UEdGraphPin* TamperSystemPin = GetTamperSystemPin();
	if (!TamperSystemPin || (!TamperSystemPin->DefaultObject && !TamperSystemPin->LinkedTo.Num()))
	{
		MessageLog.Error(*LOCTEXT("AddTamper_NoOuter", "Tamper System is required in @@").ToString(), this);
	}
}

bool UK2Node_ApplyTamperObject::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const
{
	return Super::IsCompatibleWithGraph(TargetGraph);
}


#undef LOCTEXT_NAMESPACE
