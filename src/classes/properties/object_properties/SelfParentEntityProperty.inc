<?php

/**
 * Class ParentEntityProperty
 */
class SelfParentEntityProperty extends ParentEntityProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'self_parent',
        'default_reference'           => '%toolbox_info_entity_type%',
        'default_drupal_type'         => '%toolbox_info_entity_type%',
        'default_name'                => 'parent_%toolbox_info_entity_type%',
        'default_label'               => 'Parent %toolbox_info_labels_single_lowercase%',
        'default_description'         => 'The %toolbox_info_entity_type% parent %toolbox_info_labels_single_lowercase%.',
        'default_has_revisions'       => TRUE,
        'default_has_translations'    => FALSE,
        'default_key'                 => 'parent_%toolbox_info_entity_type%',
        'default_schemas_fields_name' => array(
          'base'              => 'parent_%toolbox_info_entity_type%_id',
          'revision'          => 'parent_%toolbox_info_entity_type%_id',
          'relation'          => 'parent_%toolbox_info_entity_type%_id',
          'relation_revision' => 'parent_%toolbox_info_entity_type%_id',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'The {%toolbox_info_tables_base%}.%toolbox_info_keys_id%.',
          ),
          'revision' => array(
            'description' => 'The {%toolbox_info_tables_base%}.%toolbox_info_keys_id% revision.',
          ),
        ),
        'default_forms'               => array(
          'edit' => array(
            'required' => FALSE,
          ),
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}