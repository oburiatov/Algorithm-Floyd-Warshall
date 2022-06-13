import * as go from "gojs";

export function init() {
    var $ = go.GraphObject.make;
    
    const myDiagram =
      $(go.Diagram, "myDiagramDiv",
          {
            // double-click in background creates new node
            "clickCreatingTool.archetypeNodeData": {},
            "undoManager.isEnabled": true
          });
    
    myDiagram.nodeTemplate =
      $(go.Node, "Spot",
        { locationSpot: go.Spot.Center, locationObjectName: "SHAPE" },
        // remember the location, which is at the center of the circle
        new go.Binding("location", "loc", go.Point.parse).makeTwoWay(go.Point.stringify),
        $(go.Shape, "Circle",
          {
            name: "SHAPE", fill: "steelblue", width: 40, height: 40,
            // allow users to draw links to and from this circle
            portId: "", cursor: "pointer",
            fromLinkable: true, toLinkable: true,
            fromLinkableDuplicates: true, toLinkableDuplicates: true,
            fromLinkableSelfNode: true, toLinkableSelfNode: true
          }),
        // show in-place editable text, by default above the circle
        $(go.TextBlock, "abc",
          { alignment: new go.Spot(0.5, 0.5, 0, -30), editable: true },
          // TwoWay Binding automatically remembers text edits
          new go.Binding("text").makeTwoWay())
      );
    
    myDiagram.linkTemplate =
      $(go.Link,
        { relinkableFrom: true, relinkableTo: true },
        $(go.Shape, { stroke: "steelblue", strokeWidth: 1.5 }),
        $(go.Shape, { toArrow: "OpenTriangle", stroke: "steelblue" })
      );
    
    myDiagram.model = new go.GraphLinksModel(
      [
        { key: 1, text: "Alpha", loc: "0 0" },
        { key: 2, text: "Beta", loc: "150 0" },
        { key: 3, text: "Gamma", loc: "-75 150" },
        { key: 4, text: "Delta", loc: "75 150" }
      ],
      [
        { from: 1, to: 2 },
        { from: 1, to: 3 },
        { from: 2, to: 2 },
        { from: 3, to: 4 },
        { from: 4, to: 3 },
        { from: 4, to: 1 }
      ]);
    }