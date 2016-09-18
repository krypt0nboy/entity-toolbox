<?php

/**
 * Class PropertyValueBuilder
 */
class EntityToolboxInfoPropertyBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class'          => 'EntityToolboxInfoPropertyModel',
        'key_builders_classes' => array(
          'callbacks'             => 'EntityToolboxInfoPropertyCallbacksBuilder',
          'schemas_fields_name'   => 'EntityToolboxInfoPropertySchemasFieldsNameBuilder',
          'schemas_fields'        => 'EntityToolboxInfoPropertySchemasFieldsBuilder',
          'value'                 => 'EntityToolboxInfoPropertyValueBuilder',
          'forms'                 => 'EntityToolboxInfoPropertyFormsBuilder',
          'tables'                => 'EntityToolboxInfoPropertyTablesBuilder',
        )
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * Builds the value "type".
   */
  protected function buildType() {

  }

  /**
   * Builds the value "php type".
   */
  protected function buildPhpType() {

  }

  /**
   * Builds the value "drupal type".
   */
  protected function buildDrupalType() {
    $defaultBuild = $this->buildKeyDefault('drupal type');
    if ($this->isMultiple) {
      return preg_match('/list<\w+>/', $defaultBuild) ? $defaultBuild : "list<$defaultBuild>";
    }
    else {
      $build = preg_match('/list<(?P<type>.+)>/', $defaultBuild, $matches) ? $matches['type'] : $defaultBuild;

      return $build;
    }
  }

  /**
   * Builds the value "reference".
   *
   * @return null|string
   */
  protected function buildReference() {
    return NULL;
  }

  /**
   * Builds the value "key".
   *
   * @return null|string
   */
  protected function buildPropertyKey() {
    if (!$this->getIsMultiple() || $this->getBuild('serialize')) {
      return $this->buildKeyDefault('key');
    }
    else {
      if ($this->isMultiple && !$this->getBuild('serialize')) {
        return NULL;
      }
    }
  }

  /**
   * Builds the value "has_revisions".
   */
  protected function buildHasRevisions() {
    $entity_type_has_revisions = $this->getHookBuilder()
                                      ->getBuild('has_revisions');
    if ($entity_type_has_revisions) {
      $return = $this->buildKeyDefault('has_revisions');

      return $return;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Builds the value "has_translations".
   *
   * @return bool
   */
  protected function buildHasTranslations() {
    $entity_type_has_translations = $this->getHookBuilder()
                                         ->getBuild('has_translations');
    if ($entity_type_has_translations) {
      $return = $this->buildKeyDefault('has_translations');

      return $return;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Builds the value "multiple".
   *
   * @return bool
   */
  protected function buildMultiple() {
    return $this->isMultiple;
  }

  /**
   * Builds the value "serialize".
   */
  protected function buildSerialize() {
  }

  /**
   * Builds the value "label".
   */
  protected function buildLabel() {
  }

  /**
   * Builds the value "description".
   */
  protected function buildDescription() {
  }

  /**
   * Builds the value "required".
   */
  protected function buildRequired() {
  }

  /**
   * Builds the value "forms".
   */
  protected function buildForms() {
    return $this->getKeyBuilder('forms')->build();
  }

  /**
   * Builds the value "is_unique".
   */
  protected function buildIsUnique() {
  }

  /**
   * Builds the value "tables".
   */
  protected function buildTables() {
    if ($this->isMultiple) {
      return $this->getKeyBuilder('tables')->build();
    }
    else {
      return array();
    }
  }

  /**
   * Builds the value "schemas_fields".
   */
  protected function buildSchemasFields() {
    return $this->getKeyBuilder('schemas_fields')->build();
  }

  /**
   * Builds the value "schemas_fields_name".
   */
  protected function buildSchemasFieldsName() {
    return $this->getKeyBuilder('schemas_fields_name')->build();
  }

  /**
   * @param $preValidatedBuild
   * @return mixed
   */
  protected function validateSchemasFieldsName($preValidatedBuild) {
    return $preValidatedBuild;
  }

  /**
   * @param $build
   * @return null
   */
  protected function validateReference($build) {
    if ($this->isValueTemplate($build)) {
      return NULL;
    }
    else {
      return $build;
    }
  }

  /**
   * Builds the value "value".
   */
  protected function buildValue() {
    return $this->getKeyBuilder('value')->build();
  }

  /**
   * Builds the value "callbacks".
   */
  protected function buildCallbacks() {
    return $this->getKeyBuilder('callbacks')->build();
  }

  /**
   * Builds the value "views expose".
   */
  protected function buildViewsExpose() {
  }

  /**
   * Builds the value "weight".
   */
  protected function buildWeight() {
  }

  /**
   * Builds "self_numeric_value".
   */
  protected function buildSelfNumericProperty() {
  }

  /*** VALIDATION METHODS ***/

  /*** VALIDATION METHODS END ***/

}