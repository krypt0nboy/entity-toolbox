<?php

/**
 * Class TemplatingTraits
 */
trait TemplatingTraits {
  /**
   * @var string $selfExtractMarker
   */
  protected $selfExtractMarker;
  /**
   * @var string $selfReplaceMarker
   */
  protected $selfReplaceMarker;
  /**
   * @var array $templateVars
   *   The vars to be used when processing a value template.
   */
  protected $templateVars = array();

  /**
   * @return string
   */
  public function getSelfExtractMarker() {
    return $this->selfExtractMarker;
  }

  /**
   * @param string $selfExtractMarker
   */
  public function setSelfExtractMarker($selfExtractMarker) {
    $this->selfExtractMarker = $selfExtractMarker;
  }

  /**
   * @return string
   */
  public function getSelfReplaceMarker() {
    return $this->selfReplaceMarker;
  }

  /**
   * @param string $selfReplaceMarker
   */
  public function setSelfReplaceMarker($selfReplaceMarker) {
    $this->selfReplaceMarker = $selfReplaceMarker;
  }

  /**
   * @param null $key
   * @return array
   */
  public function getTemplateVars($key = NULL) {
    return isset($key) ? $this->templateVars[$key] : $this->templateVars;
  }

  /**
   * @param array $templateVars
   */
  protected function setTemplateVars($templateVars) {
    $this->templateVars = $templateVars;
  }

  /**
   * @param $name
   * @param $value
   */
  protected function updateTemplateVar($name, $value) {
    $this->templateVars[$name] = $value;
  }

  /**
   * @param array $vars
   */
  protected function updateTemplateVars(array $vars = array()) {
    $this->templateVars += $vars;
  }

  /**
   * @param $value
   * @return int
   */
  protected function isValueTemplate($value) {
    if (!is_array($value)) {
      return preg_match('/%\w+%/', $value);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Self extractor.
   *
   * @return array
   */
  public function extractSelfVars() {
    return $this->extractTemplateVars($this, $this->selfExtractMarker, $this->selfReplaceMarker);
  }

  /**
   * Extract the template vars.
   *
   * @param mixed  $source
   * @param string $extractMarker
   * @param string $replaceMarker
   *
   * @return array
   */
  public function extractTemplateVars($source, $extractMarker, $replaceMarker) {
    $toExtracts = array();
    $extract    = array();
    $sourceType = gettype($source);
    switch ($sourceType) {
      case 'object':
        $vars = array_keys(get_class_vars(get_class($this)));
        foreach ($vars as $var) {
          if (preg_match('/^' . $extractMarker . '\w+/', $var)) {
            $toExtracts[camelcase2lowercase($var)] = $var;
          }
        }
        foreach ($toExtracts as $key => $toExtract) {
          $extract[$key] = $this->extractTemplateVar($toExtract, $key);
        }

        return $this->flattenExtract($extractMarker, $replaceMarker, $extract);
        break;
      case 'array':
        return $this->flattenExtract($extractMarker, $replaceMarker, $source);
        break;
      default:
        break;
    }
  }

  /**
   * Extract a template var value.
   *
   * @param string $var
   * @param string $lowerCaseVar
   *
   * @return mixed
   */
  protected function extractTemplateVar($var, $lowerCaseVar) {
    $extractMethod = 'extract' . ucfirst($var);
    if (method_exists($this, $extractMethod)) {
      return $extractMethod();
    }
    else {
      return $this->__get($lowerCaseVar);
    }
  }

  /**
   * Flattens an template vars extract.
   *
   * @param string      $extractMarker
   * @param string      $replaceMarker
   * @param array       $extract
   * @param null|string $templateKey
   *
   * @return array
   */
  protected function flattenExtract($extractMarker, $replaceMarker, $extract, $templateKey = NULL) {
    $serialized = array();
    foreach ($extract as $varKey => $varExtract) {
      $newKey = isset($templateKey) ? $templateKey . '_' . $varKey : preg_replace('/^' . $extractMarker . '/', $replaceMarker, $varKey);
      if (is_array($varExtract)) {
        $serialize = $this->flattenExtract($extractMarker, $replaceMarker, $varExtract, $newKey);
        foreach ($serialize as $subVarKey => $subVarExtract) {
          $subVarKey              = preg_replace('/[[:blank:]]/', '_', $subVarKey);
          $serialized[$subVarKey] = $subVarExtract;
        }
      }
      else {
        $newKey              = preg_replace('/[[:blank:]]/', '_', $newKey);
        $serialized[$newKey] = $varExtract;
      }
    }

    return $serialized;
  }
}