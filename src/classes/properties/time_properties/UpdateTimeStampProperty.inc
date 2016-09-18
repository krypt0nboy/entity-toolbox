<?php

/**
 * Class UpdateTimeStampProperty
 */
class UpdateTimeStampProperty extends TimeStampProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'updated',
        'default_name'                => 'changed',
        'default_label'               => 'Updated',
        'default_description'         => 'The UNIX timestamp when the toolbox_info_labels_single_lowercase% was last updated.',
        'default_key'                 => 'changed',
        'default_schemas_fields_name' => array(
          'base'     => 'changed',
          'revision' => 'changed',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'The UNIX timestamp when the %toolbox_info_entity_type% was last updated.',
          ),
          'revision' => array(
            'description' => 'The %toolbox_info_entity_type% last update time revision.',
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}