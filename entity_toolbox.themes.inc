<?php

/**
 * Themes a list of entity bundles.
 *
 * @param $variables
 *   Variables provided.
 *
 * @return string
 */
function theme_entity_add_list($variables) {
  $entity_type = $variables['type'];
  $content     = $variables['content'];

  if (isset($content)) {
    $output = "<dl class=\"$entity_type-list\">";
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= "</dl>";
  }
  else {
    $toolbox_info  = entity_toolbox_get_info($entity_type);
    $bundle_entity = $toolbox_info['bundle entity'];
    $message       = t(
      "Entities cannot be added because you have not created any types yet. Go to the <a href=\"@create-entity-type\">$entity_type type creation page</a> to add a new type.",
      array('@create-entity-type' => url(entity_get_path($bundle_entity, 'admin') . '/add'))
    );
    $output        = "<p>";
    $output .= $message;
    $output .= "</p>";
  }

  return $output;
}