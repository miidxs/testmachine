//
//  XPathQuery.m
//  FuelFinder
//
//  Created by Matt Gallagher on 4/08/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//

#import "XPathQuery.h"

#import <libxml/tree.h>
#import <libxml/parser.h>
#import <libxml/HTMLparser.h>
#import <libxml/xpath.h>
#import <libxml/xpathInternals.h>

NSDictionary *DictionaryForNode(xmlNodePtr currentNode, NSMutableDictionary *parentResult)
{
    NSMutableDictionary *resultForNode = [NSMutableDictionary dictionary];
    
    if (currentNode->name)
    {
        NSString *currentNodeContent =
            [NSString stringWithCString:(const char *)currentNode->name encoding:NSUTF8StringEncoding];
        [resultForNode setObject:currentNodeContent forKey:@"nodeName"];
    }
    
    if (currentNode->content)
    {
        NSString *currentNodeContent =
            [NSString stringWithCString:(const char *)currentNode->content encoding:NSUTF8StringEncoding];
        
        if ([[resultForNode objectForKey:@"nodeName"] isEqual:@"text"] && parentResult)
        {
            [parentResult
                setObject:
                    [currentNodeContent
                        stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]]
                forKey:@"nodeContent"];
            return nil;
        }
        
        [resultForNode setObject:currentNodeContent forKey:@"nodeContent"];
    }
    
    xmlNodePtr childNode = currentNode->children;
    if (childNode)
    {
        NSMutableArray *childContentArray = [NSMutableArray array];
        while (childNode)
        {
            NSDictionary *childDictionary = DictionaryForNode(childNode, resultForNode);
            if (childDictionary)
            {
                [childContentArray addObject:childDictionary];
            }
            childNode = childNode->next;
        }
        if ([childContentArray count] > 0)
        {
            [resultForNode setObject:childContentArray forKey:@"nodeChildArray"];
        }
    }
    
    return resultForNode;
}

NSArray *PerformXPathQuery(xmlDocPtr doc, NSString *query)
{
    xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj; 

    /* Create xpath evaluation context */
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL)
    {
        NSLog(@"Unable to create XPath context.");
        [NSException raise:@"TestMachine" format:@"Unable to create XPath context."];  // PETER
        return nil;
    }
    
    /* Evaluate xpath expression */
    xpathObj = xmlXPathEvalExpression((xmlChar *)[query cStringUsingEncoding:NSUTF8StringEncoding], xpathCtx);
    if(xpathObj == NULL) {
        NSLog(@"Unable to evaluate XPath.");
        [NSException raise:@"TestMachine" format:@"Unable to evaluate XPath."];  // PETER
        return nil;
    }
    
    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    if (!nodes)
    {
        NSLog(@"Nodes was nil.");
        [NSException raise:@"TestMachine" format:@"Nodes was nil."];  // PETER
        return nil;
    }
    
    NSMutableArray *resultNodes = [NSMutableArray array];
    for (NSInteger i = 0; i < nodes->nodeNr; i++)
    {
        NSDictionary *nodeDictionary = DictionaryForNode(nodes->nodeTab[i], nil);
        if (nodeDictionary)
        {
            [resultNodes addObject:nodeDictionary];
        }
    }

    /* Cleanup */
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx); 
    
    return resultNodes;
}

NSArray *PerformHTMLXPathQuery(NSData *document, NSString *query)
{
    xmlDocPtr doc;

    /* Load XML document */
    doc = htmlReadMemory([document bytes], [document length], "", NULL, HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
    
    if (doc == NULL)
    {
        NSLog(@"Unable to parse.");
        [NSException raise:@"TestMachine" format:@"Unable to parse."];  // PETER
        return nil;
    }
    
    NSArray *result = PerformXPathQuery(doc, query);
    xmlFreeDoc(doc); 
    
    return result;
}

NSArray *PerformXMLXPathQuery(NSData *document, NSString *query)
{
    xmlDocPtr doc;
    
    /* Load XML document */
    doc = xmlReadMemory([document bytes], [document length], "", NULL, XML_PARSE_RECOVER);
    
    if (doc == NULL)
    {
        NSLog(@"Unable to parse.");
        [NSException raise:@"TestMachine" format:@"Unable to parse."];  // PETER
        return nil;
    }
    
    NSArray *result = PerformXPathQuery(doc, query);
    xmlFreeDoc(doc); 
    
    return result;
}
