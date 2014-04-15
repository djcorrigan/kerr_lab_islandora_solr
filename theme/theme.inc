<?php

/* Edited by Evan Jackson
   March 14 2014
   Added custom functionality for Drupal search results 
   Edited by Evan Jackson
   March 20 2014
   Added custom thumbnails for Drupal search results 
   Edited by Evan Jackson
   April 12 2014
   Added more custom thumbnails */

/**
 * @file
 * Theme functions for the Islandora Solr Search module.
 */


/**
 * Prepares variables for islandora_solr_wrapper templates.
 *
 * Default template: theme/islandora-solr-wrapper.tpl.php.
 *
 * @global string $base_url
 *
 * @param array $variables
 *   An associative array containing:
 *   - results: Rendered primary display
 *   - secondary_profiles: (optional) Rendered list of secondary display
 *     profiles
 *   - elements: additional elements to populate the results page
 *     - pager: (optional) Rendered pager
 *     - solr_total: (optional) Total amount of documents found.
 *     - solr_start: (optional) Solr start position
 *     - solr_end: (optional) Solr end position
 *
 * @see islandora_solr_theme()
 * @see IslandoraSolrResults::displayResults()
 */
function islandora_solr_preprocess_islandora_solr_wrapper(&$variables) {
  global $base_url;
  $variables['base_url'] = $base_url;

  $elements = $variables['elements'];

  // Make all variables in 'elements' available as variables in the template
  // file.
  foreach ($variables['elements'] as $key => $value) {
    $variables[$key] = $value;
  }

  // Results count.
  $total = $elements['solr_total'];
  $end = $elements['solr_end'];
  $start = $elements['solr_start'] + ($total > 0 ? 1 : 0);

  // Format numbers.
  $total = number_format($total, 0, '.', ',');
  $end = number_format($end, 0, '.', ',');
  $start = number_format($start, 0, '.', ',');

  $variables['islandora_solr_result_count'] = t('(@start - @end of @total)', array(
    '@start' => $start,
    '@end' => $end,
    '@total' => $total,
  ));
}

/**
 * Prepares variables for islandora_solr templates.
 *
 * Default template: theme/islandora-solr.tpl.php.
 */
function islandora_solr_preprocess_islandora_solr(&$variables) {
  $results = $variables['results'];
  foreach ($results as $key => $result) {
    $drupal_result = $result['solr_doc']; //a Drupal search result
    if (isset($drupal_result['bundle_name'])) //only Drupal results have the 'bundle_name' element
    {
      /* Set Drupal search result thumbnails based on content type */
      $bundle = $drupal_result['bundle_name'];
      $content_type = $bundle['value']; //Drupal content type
      if ($content_type == 'Blog entry') //content type: blog entry
        $result['thumbnail_url'] = 'sites/default/files/search_thumbnails/blog.png';
      else if ($content_type == 'Presentation') //content type: presentation
        $result['thumbnail_url'] = 'sites/default/files/search_thumbnails/presentation.png';
      else if ($content_type == 'Spreadsheet') //content type: spreadsheet
        $result['thumbnail_url'] = 'sites/default/files/search_thumbnails/spreadsheet.png';
      else if ($content_type == 'Word/Text Document') //content type: word/text document
        $result['thumbnail_url'] = 'sites/default/files/search_thumbnails/document_text.png';
      else if ($content_type == 'Book page') //content type: book page
	$result['thumbnail_url'] = 'sites/default/files/search_thumbnails/book.png';
      else if ($content_type == 'Calendar Event') //content type: calendar event
	$result['thumbnail_url'] = 'sites/default/files/search_thumbnails/calendar.png';
      else if ($content_type == 'HRMS Form') //content type: hrms form
	$result['thumbnail_url'] = 'sites/default/files/search_thumbnails/hrms.png';
      else if ($content_type == 'Inventory Item') //content type: inventory item
	$result['thumbnail_url'] = 'sites/default/files/search_thumbnails/inventory_item.jpg';
      else if ($content_type == 'NMR form') //content type: nmr form
	$result['thumbnail_url'] = 'sites/default/files/search_thumbnails/nmr.png';
      else if ($content_type == 'Order Item') //content type: order item
	$result['thumbnail_url'] = 'sites/default/files/search_thumbnails/order_item.jpg';
      else if ($content_type == 'Sequence Data') //content type: sequence data
	$result['thumbnail_url'] = 'sites/default/files/search_thumbnails/sequence_data.png';
      else //content type not defined above (default image)
        $result['thumbnail_url'] = 'sites/default/files/search_thumbnails/default.png';
      /* Set Drupal search result links */
      $node_url_array = explode("node/", $result['object_url']); //get node ID
      $node_id = $node_url_array[1]; //Drupal node ID
      $result['object_url'] = "node/" . $node_id; //Drupal node URL
    }
    // Thumbnail.
    $path = url($result['thumbnail_url'], array('query' => $result['thumbnail_url_params']));
    $image = theme('image', array('path' => $path));

    $options = array('html' => TRUE);
    if (isset($result['object_label'])) {
      $options['attributes']['title'] = $result['object_label'];
    }
    if (isset($result['object_url_params'])) {
      $options['query'] = $result['object_url_params'];
    }
    if (isset($result['object_url_fragment'])) {
      $options['fragment'] = $result['object_url_fragment'];
    }
    // Thumbnail link.
    $variables['results'][$key]['thumbnail'] = l($image, $result['object_url'], $options);
  }
}

/**
 * Prepares variables for islandora_solr_facet templates.
 *
 * Default template: theme/islandora-solr-facet.tpl.php.
 */
function islandora_solr_preprocess_islandora_solr_facet(&$variables) {
  $buckets = $variables['buckets'];
  if ($variables['hidden']) {
    $variables['classes_array'][] = 'hidden';
  }
}

/**
 * Returns HTML for an islandora_solr_facet_wrapper.
 *
 * @param array $variables
 *   An associative array containing:
 *   - title: A string to use as the header/title.
 *   - content: A string containing the content being wrapped.
 *
 * @ingroup themeable
 */
function theme_islandora_solr_facet_wrapper($variables) {
  $output = '<div class="islandora-solr-facet-wrapper">';
  $output .= '<h3>' . $variables['title'] . '</h3>';
  $output .= $variables['content'];
  $output .= '</div>';
  return $output;
}
