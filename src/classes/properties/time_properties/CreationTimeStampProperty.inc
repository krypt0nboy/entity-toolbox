<?php

/**
 * Class CreationTimeStampProperty
 */
class CreationTimeStampProperty extends TimeStampProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'created',
        'default_name'                => 'created',
        'default_label'               => 'Created',
        'default_description'         => 'The UNIX timestamp when the %entity_labels_single_lowercase% was created.',
        'default_key'                 => 'created',
        'default_has_revisions'       => FALSE,
        'default_required'            => TRUE,
        'default_schemas_fields_name' => array(
          'base'     => 'created',
          'revision' => 'created_revision',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'A UNIX timestamp.',
          ),
          'revision' => array(
            'description' => 'A UNIX timestamp revision.',
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}