<?php

/**
 * Class UserProperty
 */
class DisplayProperty extends EntityProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'             => 'display',
        'default_drupal_type'      => 'list<node>',
        'default_reference'        => 'node',
        'default_multiple'         => TRUE,
        'default_has_revisions'    => TRUE,
        'default_has_translations' => FALSE,
        'default_name'             => 'displays',
        'default_label'            => '%toolbox_info_labels_single% displays',
        'default_description'      => 'The %toolbox_info_labels_single% display.',
        'default_tables'           => array(
          'relation'          => '%toolbox_info_entity_type%_displays',
          'relation_revision' => '%toolbox_info_entity_type%_displays_revision',
        ),
        'default_schemas_fields_name' => array(
          'base'              => '%reference_info_entity_keys_id%',
          'revision'          => '%reference_info_entity_keys_id%',
          'relation'          => '%reference_info_entity_keys_id%',
          'relation_revision' => '%reference_info_entity_keys_id%',
        ),
        'default_forms'            => array(
          'edit' => array(
            'expose' => FALSE
          )
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}