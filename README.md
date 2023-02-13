# ClueSystem

This is a plugin designed to make creating clue systems a lot easier and simpler. 

When you download this plugin, you need to extract it in the Plugins folder of your project: 
 - ProjectFolder
    - Plugins
        - ClueSystem
    
If you have no Plugins folder, then simply add one



Using the System: 

- [Blueprints](#blueprints)
  * [CBP_Clue](#cbp_clue)
  * [CBP_ClueInspector](#cbp_clueinspector)
- [Main C++ Classes](#main-c-classes)
  * [PrimaryDataAsset_Clue](#primarydataasset_clue)
  * [ClueSetupComponent](#cluesetupcomponent)
  * [EClueLocation](#ecluelocation)
- [UI](#ui)
   * [UI_Clues](#ui_clues)
   * [CWB_ClueSlot](#cwb_clueslot)
   * [CWB_ClueSection](#cwb_cluesection)
   * [CWB_ClueListManager](#cwb_cluelistmanager)
   * [CWB_ClueViewer](#cwb_clueviewer)

# Blueprints

## CBP_Clue

This is main Blueprint to place a Clue in the World. It has a UPROPERTY to control what clue they are, that is only editable on instances of the class in the World. 

![image](https://user-images.githubusercontent.com/50571566/218344852-2dd459ec-d44e-4e36-be95-548f813d820a.png)

You can control whether or not to load in the mesh that is held on the Primary Data Asset on Construction. You may want to turn it off it is a complex mesh or don't think it is necessary. 
Alternatively, you may want it to easily compare meshes in the world and only having to change one thing (in the Data Asset)

![image](https://user-images.githubusercontent.com/50571566/218344918-6d2856f9-2f4f-4035-ba26-a19e5af7e2aa.png)

To actually pickup the Clue, there is a Blueprint Callable function that can be used: 
![image](https://user-images.githubusercontent.com/50571566/218345980-bd091199-28de-4ddb-a4ec-4df99d6d1c66.png)

I'm using it with an interface that I'm using in my main project

## CBP_ClueInspector

This Blueprint handles the inspection of the Clue. The Scene Capture is connected to a Render Texture which is then put on the UI

![image](https://user-images.githubusercontent.com/50571566/218344989-f6235668-2b38-423b-92ab-9c903a603728.png)

# Main C++ Classes

## PrimaryDataAsset_Clue

This isn't a Blueprint, but you shouldn't need to touch the C++ implementation, just create a new instance of the Data Asset. 

![image](https://user-images.githubusercontent.com/50571566/218345094-d4e914c7-29af-48a0-a721-464d05604dd9.png)
![image](https://user-images.githubusercontent.com/50571566/218345103-0ce3aebb-3269-43c2-8c9a-300e4357d27e.png)
![image](https://user-images.githubusercontent.com/50571566/218345121-d8fe86ee-0a47-4778-a2c7-0625f061e276.png)
![image](https://user-images.githubusercontent.com/50571566/218345138-a62fbc0e-6497-4fb5-a664-c2cc361e1afa.png)

You can change which type of Clue Display you want, Mesh or Image. If you had a prerendered image of a clue that you wanted to use, then you would disable UsesMesh. 
For the Mesh, you can obviously choose which static mesh you want to choose, how far away from the camera it should be and a default rotation and location offset. 
This means you can finely control where and how the Clue looks.  

![image](https://user-images.githubusercontent.com/50571566/218345194-9730e615-a23f-4d2d-936a-f45e944a1c97.png)

To make the web of clues, you simply just add in an element to the Additional Information array. 
This will automatically populate the UI with the extra spots. 

## ClueSetupComponent

This isn't a BP Class either but it needs to exist in the World. I've placed mine on the Game Mode.

![image](https://user-images.githubusercontent.com/50571566/218345444-bedca186-4841-41f3-b793-ef458362d1ae.png)

This is where you configure the Clues. In the Details Panel, you can see 

![image](https://user-images.githubusercontent.com/50571566/218345473-370077fd-fe30-445c-8d2b-eada818a4fef.png)

You can change the order of the Clues in the UI and their Location.

## EClueLocation

This is the only place in the whole project where you may need to open a C++ file, but it is really easy and you don't need any fancy software. 

![image](https://user-images.githubusercontent.com/50571566/218345588-8915a863-1aa5-438b-aecb-aa8a73f944df.png)

The Enum defines the main locations where the Clues can be found. To add more locations simply add more members to the Enum
![image](https://user-images.githubusercontent.com/50571566/218345639-ae2c26ee-28df-49ed-becf-088c855308c4.png)
![image](https://user-images.githubusercontent.com/50571566/218345649-0ee94765-7efc-48ba-a3f1-976aadec60d0.png)

# UI

## UI_Clues
The Main UI for the Plugin is the UI_Clues. 
![image](https://user-images.githubusercontent.com/50571566/218344111-848e50fb-6111-4e72-90a1-b41ece353c20.png)

This will update itself based on what clues have been collected and will be where the Player will view the Clues in greater depth.

## CWB_ClueSlot

The Clue Slot is the widget that controls what Clue to View at any time

![image](https://user-images.githubusercontent.com/50571566/218344340-e4ccb5dc-92f2-4936-a2fc-ffbf646a1f10.png)

### CWB_ClueSection

The Clue Section is designed to manage the Clue Slots, but they hold blocks based on where the Clue is located in the map. 
![image](https://user-images.githubusercontent.com/50571566/218344468-268ed8bf-9bf2-410d-bf9d-273150f1b824.png)


### CWB_ClueListManager

This Widget has no children or panel, it is designed to be placed inside a parent panel and manage the Clue Sections and provide a central place to control 
the Slots.
![image](https://user-images.githubusercontent.com/50571566/218344447-87ce1e42-a807-480d-9d9c-6d24a2f8f858.png)


### CWB_ClueViewer

The Widget that handles viewing the Clue is the CWB_ClueViewer. 
![image](https://user-images.githubusercontent.com/50571566/218344185-ad9ca63f-4378-47f7-ad78-43791a09fb0c.png)

When you select a clue to view from the Crew List Manager, this will update the clue to view. 
The Text on the right will update itself to hold the base description of the Clue. 
It will also create new widgets based on if the clue has additional information that is reliant on the player collecting other clues, so you can build a web of clues and information really easily.
